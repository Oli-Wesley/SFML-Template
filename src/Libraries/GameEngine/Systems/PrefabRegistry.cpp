#include "PrefabRegistry.h"

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
	const std::string& name, std::function<std::unique_ptr<GameObject>()> constructor)
{
	prefabRegistry[name] = constructor;
}

std::unique_ptr<GameObject> PrefabRegistry::InstantiatePrefab(std::string name)
{
	auto it = prefabRegistry.find(name);
	if (it != prefabRegistry.end())
	{
		return it->second(); // Call the prefab constructor function
	}
	return nullptr;
}

std::unique_ptr<GameObject> PrefabRegistry::InstantiatePrefab(std::string name, sf::Vector2f position)
{
	std::unique_ptr<GameObject> obj = InstantiatePrefab(name);
	obj->getTransform()->setLocalPosition(position);
	return obj;
}

std::unique_ptr<GameObject>
PrefabRegistry::InstantiatePrefab(std::string name, float x, float y)
{
	return InstantiatePrefab(name, sf::Vector2f(x, y));
}

std::unique_ptr<GameObject> PrefabRegistry::InstantiatePrefab(std::string name, std::string new_name)
{
	std::unique_ptr<GameObject> obj= InstantiatePrefab(name);
	obj->setName(new_name);
	return obj;
}


std::unique_ptr<GameObject> PrefabRegistry::InstantiatePrefab(std::string name, std::string new_name, sf::Vector2f position)
{
	std::unique_ptr<GameObject> obj = InstantiatePrefab(name, position);
	obj->setName(new_name);
	return obj;
}

std::unique_ptr<GameObject> PrefabRegistry::InstantiatePrefab(std::string name, std::string new_name, float x, float y)
{
	std::unique_ptr<GameObject> obj = InstantiatePrefab(name, sf::Vector2f(x,y));
	obj->setName(new_name);
	return obj;
}
