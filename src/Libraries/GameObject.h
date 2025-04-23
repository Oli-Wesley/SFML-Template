#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include "Components/IComponent.h"  
#include "Components/Transform.h"
#include <SFML/Graphics.hpp>

class GameObject {
public:
	GameObject();
	~GameObject();
	// lifecycle events
	void physicsUpdate(float dt);
	void update(float dt);
	void lateUpdate(float dt);
	void render(sf::RenderWindow& _window);
	void destroy();


	// usage: addComponent<ComponentType>(args)  CONSTRUCTOR OF THE COMPONENT MUST HAVE CORRESPONDING ARGUMENTS. ;
	template<typename T, typename... Args>
	T* addComponent(Args&&... args) {
		static_assert(std::is_base_of<IComponent, T>::value, "T must derive from Component");

		// Check if component already exists
		for (IComponent* comp : components) {
			if (T* existing = dynamic_cast<T*>(comp)) {
				throw std::runtime_error("Cannot Have 2 components of same type");
			}
		}

		// Create and add new component
		T* newC = new T(std::forward<Args>(args)...);
		newC->setGameObject(this);
		newC->start();
		components.push_back(newC);
		return newC;
	}

	// returns the component on this gameObject with type.
	template<typename T>
	T* getComponent() {
		for (IComponent* comp : components) {
			if (auto casted = dynamic_cast<T*>(comp))
				return casted;
		}
		return nullptr;
	}

	// returns the component on this gameObject with type.
	template<typename T>
	bool hasComponent() {
		for (IComponent* comp : components) {
			if (auto casted = dynamic_cast<T*>(comp))
				return true;
		}
		false;
	}
	void addChild(GameObject* _game_obj);

	bool isActive();
	void setActive(bool);
	bool isMaintained();
	void setMaintained(bool);

	Transform* getTransform();
	std::vector<GameObject*> getChilderen();
	GameObject* getParent();
	void setParent(GameObject*);

protected:
	std::vector<IComponent*> components;
	bool is_active = true;
	bool is_maintained = false;
	std::vector<GameObject*> childeren;
	Transform transform;
	GameObject* parent = nullptr;
};