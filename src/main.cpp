#include "Libraries/Systems/GameSystem.h"
#include "testScene.h"

int main() {

	// Add Scenes
	GameSystem::get()->Add(new testScene, "test");
	// start game
	GameSystem::get()->start("test");
	return 0;
}	