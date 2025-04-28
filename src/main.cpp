#include "Libraries/GameEngine.h"
#include "testScene.h"
#include "Libraries/GameEngine/Components.h"
#include "Libraries/GameEngine/Systems/PrefabRegistry.h"

int main() {

	// Add Prefabs
	PrefabRegistry* pref = PrefabRegistry::get();
	pref->RegisterPrefab("test", []() -> GameObject* {
		GameObject* test = new GameObject("test");
		// add components etc
		test->addComponent<SpriteRenderer>();
		test->addComponent<Texture>("../Data/Images/backButton.png");
		test->getTransform()->setLocalScale(10, 10);
		return test;
		});

	pref->RegisterPrefab("Bouncer", []() -> GameObject* {
		GameObject* bouncer = new GameObject("Bouncer");
		bouncer->getTransform()->setLocalScale(10, 10);

		bouncer->addComponent<SpriteRenderer>();
		bouncer->addComponent<Texture>("../Data/Images/ball.png");
		auto* bouncerCol = bouncer->addComponent<BoxCollider>();
		bouncerCol->setSize({ 7, 7 });

		auto* rb = bouncer->addComponent<RigidBody>();
		rb->bouncyness = 0.8f;
		rb->friction = 0.2f;
		rb->mass = 1.0f;
		return bouncer;
		});

	// Add Scenes
	GameSystem* sys = GameSystem::get();
	sys->addScene(new testScene, "test");
	

	// set window settings (not needed, there are default values)
	sys->setFramerate(120);
	sys->setTitle("SystemShowcase");
	sys->setPhysicsTimestep(90);
	sys->setResolution(800, 600);

	// start game (anything after this in main will not be called untill the game is stopped).
	sys->start("test");

	return 0;
}