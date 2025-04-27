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

void PrefabRegistry::RegisterPrefab(const std::string& name, std::function<GameObject* ()> constructor)
{
	prefabRegistry[name] = constructor;
}

GameObject* PrefabRegistry::InstantiatePrefab(std::string name)
{
	auto it = prefabRegistry.find(name);
	if (it != prefabRegistry.end()) {
		return it->second(); // Call the prefab constructor function
	}
	return nullptr;
}

GameObject* PrefabRegistry::InstantiatePrefab(std::string name, sf::Vector2f position)
{
	GameObject* obj = InstantiatePrefab(name);
	obj->getTransform()->setLocalPosition(position);
	return obj;
}

GameObject* PrefabRegistry::InstantiatePrefab(std::string name, float x, float y)
{
	return InstantiatePrefab(name, sf::Vector2f(x, y));
}
