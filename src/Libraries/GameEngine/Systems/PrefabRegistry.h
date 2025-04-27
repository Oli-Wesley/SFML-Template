#pragma once

#include <unordered_map>
#include <functional>
#include <string>
#include "../gameObject.h"	

class PrefabRegistry {
public:
	static PrefabRegistry* get();
	void RegisterPrefab(const std::string& name, std::function<GameObject* ()> constructor);
	GameObject* InstantiatePrefab(std::string name);
	GameObject* InstantiatePrefab(std::string name, sf::Vector2f position);
	GameObject* InstantiatePrefab(std::string name, float x, float y);
protected:
	PrefabRegistry() {}
	std::unordered_map<std::string, std::function<GameObject* ()>> prefabRegistry;

	static PrefabRegistry* instance;
	PrefabRegistry(PrefabRegistry const&) = delete;
	void operator=(PrefabRegistry const&) = delete;
};