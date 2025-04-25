#include "Libraries/GameEngine.h"
#include "testScene.h"

int main() {
	// Add Scenes
	GameSystem::get()->addScene(new testScene, "test");
	// start game
	GameSystem::get()->start("test");
	return 0;
}	