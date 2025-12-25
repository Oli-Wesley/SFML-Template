#pragma once
#include "../Libraries/GameEngine.h"

REGISTER_PREFAB(
	P_RenderableObject,            // name
	[]() -> std::unique_ptr<GameObject> // lambda construction func
	{
		std::unique_ptr<GameObject> game_object = std::make_unique<GameObject>("Renderable_Object");
		game_object->addComponent<SpriteRenderer>();
		game_object->addComponent<Texture>();

		return game_object;
	});