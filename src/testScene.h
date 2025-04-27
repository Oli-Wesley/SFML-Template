#pragma once

#include "Libraries/GameEngine.h"

class testScene : public Scene {
public:
	void load() override {
		// Create root
		SceneRoot = new GameObject("SceneRoot");

		// --- FLOOR ---
		GameObject* floor = new GameObject("Floor");
		floor->getTransform()->setLocalPosition({ 0, 500 });
		floor->getTransform()->setLocalScale(35, 10);
		SceneRoot->addChild(floor);

		auto* floorCol = floor->addComponent<BoxCollider>();
		floorCol->setSize(16, 8);

		floor->addComponent<SpriteRenderer>();
		floor->addComponent<Texture>("../Data/Images/Box.png");

		auto* floorRb = floor->addComponent<RigidBody>();
		floorRb->is_static = true;
		floorRb->bouncyness = 0.8f;

		// --- BOUNCER ---
		GameObject* box = new GameObject("Bouncer");
		box->getTransform()->setLocalPosition(100, 100);
		box->getTransform()->setLocalScale(10, 10);
		SceneRoot->addChild(box);
		box->addComponent<SpriteRenderer>();
		box->addComponent<Texture>("../Data/Images/ball.png");
		auto* boxCol = box->addComponent<BoxCollider>();
		boxCol->setSize({ 7, 7 });

		auto* rb = box->addComponent<RigidBody>();
		rb->bouncyness = 0.8f;
		rb->friction = 0.2f;
		rb->mass = 1.5f;
		rb->applyForce(250, 0);

		// --- Hitter ---
		GameObject* box2 = new GameObject("Bouncer1");
		box2->getTransform()->setLocalPosition(300, 100);
		box2->getTransform()->setLocalScale(15, 15);
		SceneRoot->addChild(box2);
		box2->addComponent<SpriteRenderer>();
		box2->addComponent<Texture>("../Data/Images/ball.png");
		auto* box2Col = box2->addComponent<BoxCollider>();
		box2Col->setSize({ 7, 7 });

		auto* rb2 = box2->addComponent<RigidBody>();
		rb2->bouncyness = 0.8f;
		rb2->friction = 0.2f;
		rb2->mass = 2.0;
		rb2->applyForce(-150, 0);

		// --- Hitter2 ---
		GameObject* box3 = new GameObject("Bouncer2");
		box3->getTransform()->setLocalPosition(500, 350);
		box3->getTransform()->setLocalScale(10, 10);
		SceneRoot->addChild(box3);

		box3->addComponent<SpriteRenderer>();
		box3->addComponent<Texture>("../Data/Images/ball.png");
		auto* box3Col = box3->addComponent<BoxCollider>();
		box3Col->setSize({ 7, 7 });



		auto* rb3 = box3->addComponent<RigidBody>();
		rb3->bouncyness = 0.8f;
		rb3->friction = 0.2f;
		rb3->mass = 1.0f;
		rb3->applyForce(-300, 100);

		// background
		GameObject* background = new GameObject("background");
		background->getTransform()->setLocalZheight(-1);
		background->getTransform()->setLocalScale(8, 9);
		background->addComponent <SpriteRenderer>();
		background->addComponent <Texture>("../Data/Images/GamePlayBackground.png");

		SceneRoot->addChild(background);
	}
};