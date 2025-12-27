#include "../GameObject.h"
#include "../Components/Transform.h"
#include "../ComponentInterfaces.h"
#include "../Systems/GameSystem.h"
#include <memory>
#include <iostream>

// constructor requires a name
GameObject::GameObject(std::string _name)
{
	// make transform object and set name
	transform = std::make_unique<Transform>();
	transform->setGameObject(this);
	setName(_name);
}

GameObject::~GameObject()
{
	// output when gameObject is destroyed when debug is enabled
	if (GameSystem::get()->isDebug())
		std::cout << "Destroyed GameObject with name: [" << name << "]\n";
}

// update physics with given timestep (affects all children aswell)
void GameObject::physicsUpdate(float timestep)
{
	// if enabled update
	if (is_active) {
		for (std::unique_ptr<IComponent>& comp : components) {
			IPhysicsObject* physics = dynamic_cast<IPhysicsObject*>(comp.get());
			if (physics) {
				physics->physicsUpdate(timestep);
			}
		}
		// call on all childeren
		for (std::unique_ptr<GameObject>& child : childeren) {
			child->physicsUpdate(timestep);
		}
	}
}

void GameObject::fixedUpdate(float timestep)
{
	if (is_active) {
		for (std::unique_ptr<IComponent>& comp : components) {
			IScriptableBehaviour* scriptable = dynamic_cast<IScriptableBehaviour*>(comp.get());
			if (scriptable) {
				scriptable->fixedUpdate(timestep);
			}
		}
		// call on all childeren
		for (std::unique_ptr<GameObject>& child : childeren) {
			child->fixedUpdate(timestep);
		}
	}
}

void GameObject::update(float dt)
{
	if (is_active) {
		for (std::unique_ptr<IComponent>& comp : components) {
			comp->update(dt);
		}
		// call on all childeren
		for (std::unique_ptr<GameObject>& child : childeren) {
			child->update(dt);
		}
	}
}

void GameObject::lateUpdate(float dt)
{
	if (is_active) {
		for (std::unique_ptr<IComponent>& comp : components) {
			comp->lateUpdate(dt);
		}
		// call on all childeren
		for (std::unique_ptr<GameObject>& child : childeren) {
			child->lateUpdate(dt);
		}
	}
}

std::vector<IRenderable*> GameObject::render()
{
	std::vector<IRenderable*> result;
	if (is_drawn) {
		for (std::unique_ptr<IComponent>& comp : components) {
			IRenderable* renderable = dynamic_cast<IRenderable*>(comp.get());
			if (renderable) {
				result.push_back(renderable);
			}
		}
		// call on all childeren
		for (std::unique_ptr<GameObject>& child : childeren) {
			std::vector<IRenderable*> childRenderables = child->render();
			result.insert(result.end(), childRenderables.begin(), childRenderables.end());
		}
	}
	return result;
}

void GameObject::destroy()
{
	if (pending_destroy) return; // ensure its only added to queue once.
	GameSystem::get()->addToDestroyQueue(this);
	pending_destroy = true;
}

GameObject* GameObject::addChild(std::unique_ptr<GameObject> _game_obj)
{
	GameObject* rawPtr = _game_obj.get(); // Grab the raw pointer before moving so it can be returned
	rawPtr->setParent(this);

	// Move ownership into the vector
	childeren.push_back(std::move(_game_obj));

	return rawPtr;
}

// used for moving children between objects (get this then addchild to another object) 
std::unique_ptr<GameObject> GameObject::releaseChild(GameObject* child_to_release)
{
	if (!child_to_release) return nullptr;

	// Find the unique_ptr holding the raw pointer
	auto it = std::find_if(childeren.begin(), childeren.end(),
		[&](const std::unique_ptr<GameObject>& ptr) {
			return ptr.get() == child_to_release;
		});

	if (it != childeren.end()) {
		// Use std::move to transfer ownership out of the childrens list
		std::unique_ptr<GameObject> released_ptr = std::move(*it);

		// Erase the now empty unique_ptr slot from the vector
		childeren.erase(it);

		// Reset the parent pointer
		released_ptr->parent = nullptr;

		return released_ptr;
	}
	return nullptr;
}

bool GameObject::isActive()
{
	return is_active;
}

void GameObject::setActive(bool val)
{
	// if val is different to what is currently, call onEnable or disable
	if (val != is_active)
	{
		is_active = val;

		if (val) {
			for (std::unique_ptr<IComponent>& comp : components) {
				comp->onEnable();
			}
		}
		else {
			for (std::unique_ptr<IComponent>& comp : components) {
				comp->onDisable();
			}
		}
	}
}

bool GameObject::isDrawn()
{
	return is_drawn;
}

void GameObject::setDrawn(bool val)
{
	is_drawn = val;
}

std::vector<IComponent*> GameObject::getAllComponents()
{
	// Construct a new vector of raw pointers from the owning unique_ptrs
	std::vector<IComponent*> rawComponents;
	rawComponents.reserve(components.size());

	for (const std::unique_ptr<IComponent>& comp : components) {
		rawComponents.push_back(comp.get());
	}

	return rawComponents;
}

// returns all children, including childeren of childeren. 
std::vector<GameObject*> GameObject::getAllChilderen()
{
	std::vector<GameObject*> result;

	for (const std::unique_ptr<GameObject>& child : childeren) {
		// child is a unique_ptr, use .get() to push raw pointer
		result.push_back(child.get());

		// get all children from the child (this recursively returns vector<GameObject*>)
		std::vector<GameObject*> sub_children = child->getAllChilderen();
		result.insert(result.end(), sub_children.begin(), sub_children.end());
	}

	// return up the chain
	return result;
}

Transform* GameObject::getTransform()
{
	return transform.get();
}


sf::FloatRect GameObject::getGlobalBounds()
{
		for (std::unique_ptr<IComponent>& comp : components) {
			IRenderable* renderable = dynamic_cast<IRenderable*>(comp.get());
			if (renderable) {
				return renderable->getGlobalBounds();
			}
		}
	return sf::FloatRect(0,0,0,0);
}


sf::FloatRect GameObject::getGlobalBoundsWithChilderen()
{
	std::vector<IRenderable*> all_active_child_renderables = render();
	sf::FloatRect size(0, 0, 0, 0);
	for (IRenderable* i : all_active_child_renderables) {
		size = helpers::growRectToFit(size, i->getGlobalBounds());
	}
	return size;
}

bool GameObject::wasRenderedLastFrame()
{
	if (is_drawn) {
		for (std::unique_ptr<IComponent>& comp : components) {
			IRenderable* renderable = dynamic_cast<IRenderable*>(comp.get());
			if (renderable) {
				return renderable->wasRenderedLastFrame();
			}
		}
	}
	return false;
}

bool GameObject::wasRenderedLastFrameWithChilderen()
{
	std::vector<IRenderable*> all_active_child_renderables = render();
	for (IRenderable* i : all_active_child_renderables) {
		if (i->wasRenderedLastFrame())
			return true;
	}
	return false;
}

std::vector<GameObject*> GameObject::getChilderen()
{
	std::vector<GameObject*> result;
	for (const std::unique_ptr<GameObject>& child : childeren) {
		result.push_back(child.get());
	}
	return result;
}

// gets the first child with the name specified
GameObject* GameObject::getChildByName(std::string name)
{
	for (std::unique_ptr<GameObject>& child : childeren) {
		if (child->getName() == name)
			return child.get();
	}
	return nullptr;
}

GameObject* GameObject::getParent()
{
	return parent;
}

void GameObject::setParent(GameObject* _parent)
{
	parent = _parent;
}

std::string GameObject::getName()
{
	return name;
}

void GameObject::setName(std::string _name)
{
	name = _name;
}

void GameObject::outputChildrenTree()
{
	std::cout << "----------------------------------------\n";
	outputChildrenTree("");
	std::cout << "----------------------------------------\n";
}


void GameObject::outputChildrenTree(std::string prefix)
{
	// if first element, just display name
	if (prefix.empty()) {
		std::cout << "[" << getName() << "]  Components:(" << getAllComponents().size() + 1 << ")" << std::endl;
	}

	// go through all children
	for (size_t i = 0; i < childeren.size(); ++i) {
		const auto& child = childeren[i];
		if (!child) continue;

		// Check if this is the last child in the current list
		bool is_last_child = (i == childeren.size() - 1);

		// Define the current line's connector ('L' for last, '|' otherwise)
		std::string connector = is_last_child ? "L-" : "|-";

		// Define the prefix for the next depth level
		std::string next_prefix = prefix + (is_last_child ? "     " : "|    ");

		// Output the child's line
		std::cout << prefix << connector <<"[" << child->getName() << "]  Components:(" <<  child->getAllComponents().size()+1 << ")" << std::endl;

		// Recurse for the child's children
		child->outputChildrenTree(next_prefix);
	}
}
