#include "Libraries/GameEngine.h"

#include "Libraries/GameEngine/Components.h"
#include "Scenes/TitleScene.h"
#include "Libraries/GameEngine/Systems/PrefabRegistry.h"
#include "Libraries/GameEngine/Tools/AssetDatabase.h"
#include "Prefabs/PrefabLoader.h" // need to include as this registers all the prefabs.

int main() {
	srand(time(0)); // setup random numbers
	// Add Scenes
	GameSystem* sys = GameSystem::get();
	 sys->addScene(new TitleScene, "TitleScene");
	// set window settings (not needed, there are default values)
	sys->setFramerate(120);
	sys->setTitle("Game Engine");
	sys->setResolution(960, 540);

	AssetDatabase* asd = AssetDatabase::get();

	// start game (anything after this in main will not be called untill the game is stopped).
	sys->start("TitleScene");

	return 0;
}