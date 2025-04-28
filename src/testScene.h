#pragma once

#include "Libraries/GameEngine.h"

class testScene : public Scene {
public:
	void load() override {
		// --- FLOOR ---
		GameObject* floor = new GameObject("Floor");
		floor->getTransform()->setLocalPosition({ 0, 500 });
		floor->getTransform()->setLocalScale(35, 10);
		scene_root->addChild(floor);

		auto* floorCol = floor->addComponent<BoxCollider>();
		floorCol->setSize(16, 8);

		floor->addComponent<SpriteRenderer>();
		floor->addComponent<Texture>("../Data/Images/Box.png");

		auto* floorRb = floor->addComponent<RigidBody>();
		floorRb->is_static = true;
		floorRb->bouncyness = 0.8f;

		// --- BOUNCERS ---
		GameObject* box = PrefabRegistry::get()->InstantiatePrefab("Bouncer", 200, 100);
		scene_root->addChild(box);
		auto* rb = box->getComponent<RigidBody>();
		rb->applyForce(250, 0);

		GameObject* box2 = PrefabRegistry::get()->InstantiatePrefab("Bouncer", 400, 100);
		box2->getTransform()->setLocalScale(15, 15);
		scene_root->addChild(box2);

		auto* rb2 = box2->getComponent<RigidBody>();
		rb2->applyForce(-150, 0);

		GameObject* bouncer2 = PrefabRegistry::get()->InstantiatePrefab("Bouncer", 600, 350);
		scene_root->addChild(bouncer2);

		auto* rb3 = bouncer2->getComponent<RigidBody>();
		rb3->applyForce(-300, 100);

		// background
		GameObject* background = new GameObject("background");
		scene_root->addChild(background);
		background->getTransform()->setLocalZheight(-1);
		background->getTransform()->setLocalScale(8, 9);
		background->addComponent <SpriteRenderer>();
		background->addComponent <Texture>("../Data/Images/GamePlayBackground.png");


		scene_root->addChild(PrefabRegistry::get()->InstantiatePrefab("test", 10, 10));

		
	}
};