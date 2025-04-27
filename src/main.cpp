#include "Libraries/GameEngine.h"
#include "testScene.h"
#include "Libraries/GameEngine/Components.h"
#include "Libraries/GameEngine/Systems/PrefabRegistry.h"

int main() {

	// Add Prefabs
	PrefabRegistry::get()->RegisterPrefab("test", []() -> GameObject* {
		GameObject* test = new GameObject("test");
		// add components etc
		test->addComponent<SpriteRenderer>();
		test->addComponent<Texture>("../Data/Images/backButton.png");
		return test;
		});


	// Add Scenes
	GameSystem::get()->addScene(new testScene, "test");

	// start game (anything after this in main will not be called untill the game is stopped).
	GameSystem::get()->start("test");

	return 0;
}