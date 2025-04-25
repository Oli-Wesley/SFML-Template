#include "../GameObject.h"
#include "../Components/Transform.h"
#include "../ComponentInterfaces.h"
GameObject::GameObject(std::string _name)
{
	transform.setGameObject(this);
	name = _name;

}

GameObject::~GameObject()
{
	destroy();
	delete parent;
}

void GameObject::physicsUpdate(float timestep)
{
	if (is_active) {
		for (auto& comp : components) {
			IPhysicsObject* physics = dynamic_cast<IPhysicsObject*>(comp);
			if (physics) {
				physics->physicsUpdate(timestep);
				//return; // TODO: ONLY DO ON HIGHEST IN HEIRARCHY WITH A PHYSICS OBJECT OR ISSUES MAY HAPPEN (I DONT KNOW IF THIS WILL ACTUALLY CAUSE ISSUES, BUT I THINK IT WILL SO LEAVING THIS COMMENT)
			}
		}
		// call on all childeren
		for (GameObject* child : childeren) {
			child->physicsUpdate(timestep);
		}
	}
}

void GameObject::fixedUpdate(float timestep)
{
	if (is_active) {
		for (auto& comp : components) {
			IScriptableBehaviour* scriptable = dynamic_cast<IScriptableBehaviour*>(comp);
			if (scriptable) {
				scriptable->fixedUpdate(timestep);
				//return; // TODO: ONLY DO ON HIGHEST IN HEIRARCHY WITH A PHYSICS OBJECT OR ISSUES MAY HAPPEN (I DONT KNOW IF THIS WILL ACTUALLY CAUSE ISSUES, BUT I THINK IT WILL SO LEAVING THIS COMMENT)
			}
		}
		// call on all childeren
		for (GameObject* child : childeren) {
			child->fixedUpdate(timestep);
		}
	}
}

void GameObject::update(float dt)
{
	if (is_active) {
		for (IComponent* comp : components) {
			comp->update(dt);
		}
		// call on all childeren
		for (GameObject* child : childeren) {
			child->update(dt);
		}
	}
}

void GameObject::lateUpdate(float dt)
{
	if (is_active) {
		for (IComponent* comp : components) {
			comp->lateUpdate(dt);
		}
		// call on all childeren
		for (GameObject* child : childeren) {
			child->lateUpdate(dt);
		}
	}
}

// TODO: change so rendering is based on a z_depth value (so lower numbers get drawn first) 
// will need to go in GameSystem. as currently it is done in heirarchal order which causes all parents to be drawn ontop of childeren. 
// (this will also likely be nice for camera stuff in future). ZHEIGHT IS IMPLEMENTED IN TRANSFORM but is currently unused.
// IDEAS FOR IMPLEMENTATION Change this function to take a std::vector<Irenderable*>*, recursively add all instances of IRenderable then pass this to the gameSystem to sort and render.
void GameObject::render(sf::RenderWindow* _window)
{
	if (is_active) {
		for (auto& comp : components) {
			IRenderable* renderable = dynamic_cast<IRenderable*>(comp);
			if (renderable) {
				renderable->render(_window);
			}
		}
		// call on all childeren
		for (GameObject* child : childeren) {
			child->render(_window);
		}
	}
}

void GameObject::destroy()
{
	// call destroy on all components (before deleting so they can access others if needed)
	for (IComponent* comp : components) {
		comp->onDestroy();
	}
	// delete all components
	for (IComponent* comp : components) {
		delete comp;
	}

	// empty components registry
	components.clear();
}

void GameObject::addChild(GameObject* _game_ob)
{
	childeren.push_back(_game_ob);
	_game_ob->setParent(this);
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
		if (val) {
			for (IComponent* comp : components) {
				comp->onEnable();
			}
		}
		else {
			for (IComponent* comp : components) {
				comp->onDisable();
			}
		}
	}
}

bool GameObject::isMaintained()
{
	return is_maintained;
}

void GameObject::setMaintained(bool val)
{
	is_maintained = val;
}

std::vector<IComponent*> GameObject::getAllComponents()
{
	return components;
}

Transform* GameObject::getTransform()
{
	return &transform;
}

std::vector<GameObject*> GameObject::getChilderen()
{
	return childeren;
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
