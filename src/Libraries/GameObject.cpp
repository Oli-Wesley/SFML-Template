#include "GameObject.h"
#include "Components/Transform.h"

GameObject::GameObject()
{
	Transform* temp = new Transform;
	AddComponent<Transform>(temp);
	temp->setAttatchedTo(this);
}

void GameObject::AddChild(GameObject* child)
{
	// need to fix so it checks all parents, to prevent loops. 
	if (child != parent) {
		child->parent = this;
		children.push_back(child);
	}
}

void GameObject::Awake()
{
	for (auto& pair : components)
		pair.second->Awake();

	for (GameObject* child : children)
		child->Awake();
}

void GameObject::Start()
{
	for (auto& pair : components)
		pair.second->Start();

	for (GameObject* child : children)
		child->Start();
}

void GameObject::Sleep()
{
	for (auto& pair : components)
		pair.second->Sleep();

	for (GameObject* child : children)
		child->Sleep();
}

void GameObject::Update(float dt)
{
	if (active)
	{
		for (auto& pair : components)
			pair.second->Update(dt);

		for (GameObject* child : children)
			child->Update(dt);
	}
}

void GameObject::render(sf::View* _view)
{
	if (active)
	{
		for (auto& pair : components)
			pair.second->render(_view);

		for (GameObject* child : children)
			child->render(_view);
	}
}

void GameObject::OnDestroy()
{
	{
		for (auto& pair : components) {
			pair.second->OnDestroy();
			delete pair.second;
		}
		components.clear();

		for (GameObject* child : children) {
			child->OnDestroy();
			delete child;
		}
		children.clear();
	}
}
