#include "../Scene.h"
#include "../GameObject.h"

void Scene::unload()
{
	for (GameObject* obj: game_objects) {
			delete obj;
	}
	game_objects.clear();
}
