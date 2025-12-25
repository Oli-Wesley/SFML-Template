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
	// sys->setDebug(1); // can be toggled at runtime using f3, but also can be toggled here to see the loading of assets on startup

	AssetDatabase* asd = AssetDatabase::get(); // get asset database (first time getting loads all the assets)


	// start game (anything after this in main will not be called untill the game is stopped).
	sys->start("TitleScene");

	return 0;
}