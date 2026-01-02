#include "Libraries/GameEngine.h"

#include "Libraries/GameEngine/Components.h"
#include "Scenes/TitleScene.h"
#include "Libraries/GameEngine/Tools/AssetDatabase.h"
#include "Prefabs/PrefabLoader.h" // need to include as this registers all the prefabs.
#include "Libraries/GameEngine/Tools/FileParser.h"

int main() {
	srand(time(nullptr)); // setup random numbers
	// Add Scenes
	GameSystem* sys = GameSystem::get();
	sys->addScene(new TitleScene, "TitleScene");
	// set window settings (not needed, there are default values)
	sys->setFramerate(120);
	sys->setTitle("Game Engine");
	sys->setResolution(960, 540);

	AssetDatabase::get(); // get asset database (first time getting loads all the assets)
	// start game (anything after this in main will not be called until the game is stopped).
	sys->start("TitleScene");

	return 0;
}