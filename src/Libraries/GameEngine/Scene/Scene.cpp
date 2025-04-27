#include "../Scene.h"
#include "../GameObject.h"

Scene::Scene()
{
	scene_root = new GameObject("Scene_Root");
	dont_destroy = new GameObject("Dont_Destroy");
}

Scene::~Scene()
{
	scene_root->destroy();

}

GameObject* Scene::unload()
{
	onUnload(); // call each scene's onUnload functions.
	std::vector<GameObject*>game_objects;
	for (GameObject* obj : game_objects) {
		delete obj;
	}
	game_objects.clear();
	return dont_destroy;
}

void Scene::load(GameObject* _dont_destroy)
{
	if (dont_destroy)
	{
		delete dont_destroy; // delete the old gameObject just created if a new one is given.
		dont_destroy = _dont_destroy;
	}
	
	// call each scene's individual load function.
	load();
}
