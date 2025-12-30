#include "../GameObject.h"
#include "../Components/Transform.h"
#include "../ComponentInterfaces.h"
#include "../Systems/GameSystem.h"
#include <memory>
#include <iostream>
#include "../Tools/LayerManager.h"

// constructor requires a name
GameObject::GameObject(const std::string &_name)
{
	// make transform object and set name
	transform = std::make_unique<Transform>();
	transform->setGameObject(this);
	setName(_name);
	setLayer("Default"); // set to default layer
}

GameObject::~GameObject()
{
	// output when gameObject is destroyed when debug is enabled
	if (GameSystem::get()->isDebug())
		std::cout << "Destroyed GameObject with name: [" << name << "]\n";
}

// update physics with given timestep (affects all children as well)
void GameObject::physicsUpdate(const float timestep)
{
	// if enabled update
	if (is_active) {
		for (std::unique_ptr<IComponent>& comp : components) {
			if (auto* physics = dynamic_cast<IPhysicsObject*>(comp.get())) {
				physics->physicsUpdate(timestep);
			}
		}
		// call on all children
		for (const std::unique_ptr<GameObject>& child : children) {
			child->physicsUpdate(timestep);
		}
	}
}

void GameObject::fixedUpdate(const float timestep)
{
	if (is_active) {
		for (std::unique_ptr<IComponent>& comp : components) {
			if (const auto* scriptable = dynamic_cast<IScriptableBehaviour*>(comp.get())) {
				scriptable->fixedUpdate(timestep);
			}
		}
		// call on all children
		for (const std::unique_ptr<GameObject>& child : children) {
			child->fixedUpdate(timestep);
		}
	}
}

void GameObject::update(const float dt) const {
	if (is_active) {
		for (const std::unique_ptr<IComponent>& comp : components) {
			comp->update(dt);
		}
		// call on all children
		for (const std::unique_ptr<GameObject>& child : children) {
			child->update(dt);
		}
	}
}

void GameObject::lateUpdate(const float dt) const {
	if (is_active) {
		for (const std::unique_ptr<IComponent>& comp : components) {
			comp->lateUpdate(dt);
		}
		// call on all children
		for (const std::unique_ptr<GameObject>& child : children) {
			child->lateUpdate(dt);
		}
	}
}

std::vector<IRenderable*> GameObject::render()
{
	std::vector<IRenderable*> result;
	if (is_drawn) {
		for (std::unique_ptr<IComponent>& comp : components) {
			if (auto* renderable = dynamic_cast<IRenderable*>(comp.get())) {
				result.push_back(renderable);
			}
		}
		// call on all children
		for (const std::unique_ptr<GameObject>& child : children) {
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
	rawPtr->setLayer(getLayer()); // set to same layer as parent by default.

	// Move ownership into the vector
	children.push_back(std::move(_game_obj));

	// ReSharper disable once CppDFALocalValueEscapesFunction
	return rawPtr;
}

// used for moving children between objects (get this then add child to another object)
std::unique_ptr<GameObject> GameObject::releaseChild(const GameObject* child_to_release)
{
	if (!child_to_release) return nullptr;

	// Find the unique_ptr holding the raw pointer
	const auto it = std::ranges::find_if(children,
	                               [&](const std::unique_ptr<GameObject>& ptr) {
		                               return ptr.get() == child_to_release;
	                               });

	if (it != children.end()) {
		// Use std::move to transfer ownership out of the childrens list
		std::unique_ptr<GameObject> released_ptr = std::move(*it);

		// Erase the now empty unique_ptr slot from the vector
		children.erase(it);

		// Reset the parent pointer
		released_ptr->parent = nullptr;

		return released_ptr;
	}
	return nullptr;
}

bool GameObject::isActive() const {
	return is_active;
}

void GameObject::setActive(const bool val)
{
	// if val is different to what is currently, call onEnable or disable
	if (val != is_active)
	{
		is_active = val;

		if (val) {
			for (const std::unique_ptr<IComponent>& comp : components) {
				comp->onEnable();
			}
		}
		else {
			for (const std::unique_ptr<IComponent>& comp : components) {
				comp->onDisable();
			}
		}
	}
}

bool GameObject::isDrawn() const {
	return is_drawn;
}

void GameObject::setDrawn(const bool val)
{
	is_drawn = val;
}

std::vector<IComponent*> GameObject::getAllComponents() const {
	// Construct a new vector of raw pointers from the owning unique_ptrs
	std::vector<IComponent*> rawComponents;
	rawComponents.reserve(components.size());

	for (const std::unique_ptr<IComponent>& comp : components) {
		rawComponents.push_back(comp.get());
	}

	return rawComponents;
}

// returns all children, including children of children.
std::vector<GameObject*> GameObject::getAllChildren() const {
	std::vector<GameObject*> result;

	for (const std::unique_ptr<GameObject>& child : children) {
		// child is a unique_ptr, use .get() to push raw pointer
		result.push_back(child.get());

		// get all children from the child (this recursively returns vector<GameObject*>)
		std::vector<GameObject*> sub_children = child->getAllChildren();
		result.insert(result.end(), sub_children.begin(), sub_children.end());
	}

	// return up the chain
	return result;
}

Transform* GameObject::getTransform() const {
	return transform.get();
}


sf::FloatRect GameObject::getGlobalBounds()
{
		for (std::unique_ptr<IComponent>& comp : components) {
			if (auto* renderable = dynamic_cast<IRenderable*>(comp.get())) {
				return renderable->getGlobalBounds();
			}
		}
	return {0,0,0,0};
}


sf::FloatRect GameObject::getGlobalBoundsWithChildren()
{
	const std::vector<IRenderable*> all_active_child_renderables = render();
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
			if (const auto* renderable = dynamic_cast<IRenderable*>(comp.get())) {
				return renderable->wasRenderedLastFrame();
			}
		}
	}
	return false;
}

bool GameObject::wasRenderedLastFrameWithChildren()
{
	const std::vector<IRenderable*> all_active_child_renderables = render();
	for (const IRenderable* i : all_active_child_renderables) {
		if (i->wasRenderedLastFrame())
			return true;
	}
	return false;
}

std::vector<GameObject*> GameObject::getChildren() const {
	std::vector<GameObject*> result;
	for (const std::unique_ptr<GameObject>& child : children) {
		result.push_back(child.get());
	}
	return result;
}

// gets the first child with the name specified
GameObject* GameObject::getChildByName(const std::string &child_name) const {
	for (const std::unique_ptr<GameObject>& child : children) {
		if (child->getName() == child_name)
			return child.get();
	}
	return nullptr;
}

GameObject* GameObject::getParent() const {
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

void GameObject::setName(const std::string &_name)
{
	name = _name;
}

void GameObject::outputChildrenTree()
{
	std::cout << "----------------------------------------\n";
	outputChildrenTree("");
	std::cout << "----------------------------------------\n";
}

void GameObject::setLayer(const std::string &layer_name) {
	setLayer(layer_name, false);
}

void GameObject::setLayer(const std::string &layer_name, const bool include_children) {
	if (const int new_layer = LayerManager::getLayerIndex(layer_name); new_layer  != -1) {
		setLayer(new_layer, include_children);
		return;
	}
	std::cout << "WARNING: layer (" << layer_name <<") Does not exist\n";
}

void GameObject::setLayer(const int layer_id) {
	layer = layer_id;
}

void GameObject::setLayer(const int layer_id, const bool include_children) {
	setLayer(layer_id);
	if (include_children) {
		for (const std::unique_ptr<GameObject>& child : children) {
			child->setLayer(layer_id, true);
		}
	}
}

int GameObject::getLayer() const {
	return layer;
}

std::string GameObject::getLayerId() const {
	return LayerManager::getLayerName(getLayer());
}


void GameObject::outputChildrenTree(const std::string &prefix)
{
	// if first element, just display name
	if (prefix.empty()) {
		std::cout << "[" << getName() << "]  Components:(" << getAllComponents().size() + 1 << ")" << std::endl;
	}

	// go through all children
	for (size_t i = 0; i < children.size(); ++i) {
		const auto& child = children[i];
		if (!child) continue;

		// Check if this is the last child in the current list
		bool is_last_child = (i == children.size() - 1);

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
