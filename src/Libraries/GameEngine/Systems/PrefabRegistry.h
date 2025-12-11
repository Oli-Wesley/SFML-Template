#pragma once

#include "../GameObject.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <memory> // Include for std::unique_ptr

// Register Prefab macro, individual prefabs can use this to add themselves to
// the prefabRegistry.
#define REGISTER_PREFAB(name, func)             \
  static bool name##_registered = []()          \
  {                                             \
    PrefabRegistry::get()->RegisterPrefab(#name, func); \
    return true;                                \
  }()

class PrefabRegistry
{
public:
    // get a pointer to the prefab registry singleton instance
    static PrefabRegistry* get();

    // register prefabs to the prefab registry map to be loaded elsewhere. 
    // CHANGE 1: Constructor now returns std::unique_ptr<GameObject>
    void RegisterPrefab(
        const std::string& name, std::function<std::unique_ptr<GameObject>()> constructor);

    // instantiate prefab with given name 
    std::unique_ptr<GameObject> InstantiatePrefab(std::string name);

    // instantiate prefab with given name at coords specified
    std::unique_ptr<GameObject> InstantiatePrefab(std::string name, sf::Vector2f position);

    // instantiate prefab with given name at coords specified
    std::unique_ptr<GameObject> InstantiatePrefab(std::string name, float x, float y);

    // instantiate prefab with given name and override the name on the gameObject.
    std::unique_ptr<GameObject> InstantiatePrefab(std::string name, std::string new_name);

    // instantiate prefab with given name at coords specified and override the name on the gameObject.
    std::unique_ptr<GameObject> InstantiatePrefab(std::string name, std::string new_name, sf::Vector2f position);

    // instantiate prefab with given name at coords specified and override the name on the gameObject.
    std::unique_ptr<GameObject> InstantiatePrefab(std::string name, std::string new_name, float x, float y);

protected:
    PrefabRegistry() {}

    // map for storing prefabs and their constructor functions
    std::unordered_map<std::string, std::function<std::unique_ptr<GameObject>()>> prefabRegistry;

	static PrefabRegistry* instance;
	PrefabRegistry(PrefabRegistry const&) = delete;
	void operator=(PrefabRegistry const&) = delete;
};