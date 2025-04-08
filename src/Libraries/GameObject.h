#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include "Components/IComponent.h"  

class GameObject {
public:
	GameObject();

	~GameObject() {
		OnDestroy();
	}

	// Add child to this GameObject
	void AddChild(GameObject* child);

	GameObject* GetParent(){
		return parent;
	}

	std::vector<GameObject*>& GetChildren() {
		return children;
	}

	// Component methods 
	template <std::derived_from<IComponent> T>
	void AddComponent(T* component) {
		if (components.contains(std::type_index(typeid(T)))) {
			throw std::runtime_error("Component already exists.");
			return;
		}
		// add component, and set it to be attatched to this gameObject.
		components[std::type_index(typeid(T))] = component;
		component->setAttatchedTo(this);
	}

	template <std::derived_from<IComponent> T>
	T& GetComponent() {
		auto it = components.find(std::type_index(typeid(T)));
		if (it != components.end()) {
			return *static_cast<T*>(it->second);
		}
		throw std::runtime_error("Component not found!");
	}

	// Functions on Child Objects and components
	void Awake();

	void Start();

	void Sleep();

	void Update(float dt);

	void render(sf::View* _view);

	void OnDestroy();

	std::string getId() {
		return ID;
	}

	void setId(std::string _id) {
		ID = _id;
	}

	void set_active(bool _state) {
		if (_state != active) {
			active = _state;
			if (active)
				Awake();
			else
				Sleep();
		}
	}

protected:
	std::unordered_map<std::type_index, IComponent*> components;
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	std::string ID = "Empty";
	bool active = true;
};