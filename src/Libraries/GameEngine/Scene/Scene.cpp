#include "../Scene.h"
#include "../GameObject.h"

void Scene::unload()
{
	std::vector<GameObject*>game_objects;
	for (GameObject* obj : game_objects) {
		delete obj;
	}
	game_objects.clear();
}
