#include "PrefabRegistry.h"

#include <iostream>

// Define the static member variable
PrefabRegistry* PrefabRegistry::instance = nullptr;

PrefabRegistry* PrefabRegistry::get()
{
	if (instance == nullptr)
	{
		instance = new PrefabRegistry();
	}
	return instance;
}

void PrefabRegistry::RegisterPrefab(
	const std::string& name, const std::function<std::unique_ptr<GameObject>()> &constructor)
{
	prefabRegistry[name] = constructor;
}

std::unique_ptr<GameObject> PrefabRegistry::InstantiatePrefab(const std::string &name)
{
	if (const auto it = prefabRegistry.find(name); it != prefabRegistry.end())
	{
		return it->second(); // Call the prefab constructor function
	}
	std::cout << "NO PREFAB: " << name << std::endl;
	return nullptr;
}

std::unique_ptr<GameObject> PrefabRegistry::InstantiatePrefab(const std::string &name, const sf::Vector2f position)
{
	std::unique_ptr<GameObject> obj = InstantiatePrefab(name);
	obj->getTransform()->setLocalPosition(position);
	return obj;
}

std::unique_ptr<GameObject>
PrefabRegistry::InstantiatePrefab(const std::string &name, const float x, const float y)
{
	return InstantiatePrefab(name, sf::Vector2f(x, y));
}

std::unique_ptr<GameObject> PrefabRegistry::InstantiatePrefab(const std::string &name, const std::string &new_name)
{
	std::unique_ptr<GameObject> obj= InstantiatePrefab(name);
	obj->setName(new_name);
	return obj;
}


std::unique_ptr<GameObject> PrefabRegistry::InstantiatePrefab(const std::string &name, const std::string &new_name, const sf::Vector2f position)
{
	std::unique_ptr<GameObject> obj = InstantiatePrefab(name, position);
	obj->setName(new_name);
	return obj;
}

std::unique_ptr<GameObject> PrefabRegistry::InstantiatePrefab(const std::string &name, const std::string &new_name, const float x, const float y)
{
	std::unique_ptr<GameObject> obj = InstantiatePrefab(name, sf::Vector2f(x,y));
	obj->setName(new_name);
	return obj;
}
