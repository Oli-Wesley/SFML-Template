#include "Libraries/GameEngine.h"
#include "testScene.h"

int main() {
	// Add Scenes
	GameSystem::get()->addScene(new testScene, "test");


	// start game (anything after this in main will not be called untill the game is stopped).
	GameSystem::get()->start("test");
	
	return 0;
}	