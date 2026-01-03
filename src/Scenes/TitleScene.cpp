#include "TitleScene.h"

#include <iostream>

#include "../../Libraries/GameEngine.h"
#include "../../Libraries/GameEngine/Tools/LayerManager.h"
#include "../Scripts/Button.h"

void TitleScene::load()
{
	PrefabRegistry* pref = PrefabRegistry::get();
	scene_background_color = sf::Color(69, 40, 69);

	GameObject* camera = scene_root->addChild(std::make_unique<GameObject>("Camera"));
	auto* camera_comp = camera->addComponent<Camera>(sf::Vector2i(960, 540));
	camera->getTransform()->setGlobalPosition(960.0f / 2, 540.0f / 2); // set to middle of screen (0,0 = top left);
	camera_comp->setBackgroundColor(sf::Color::Black);
	camera_comp->setScreenRect(0, 0, 0.5, 0.5); // set to half the screen size
	camera_comp->setLayer("Player", true);


	// setup second camera (exact same view, just different screen position)
	GameObject* camera2 = scene_root->addChild(std::make_unique<GameObject>("Camera"));
	auto* camera_comp2 = camera2->addComponent<Camera>(sf::Vector2i(960, 540));
	camera2->getTransform()->setGlobalPosition(960.0f / 4, 540.0f / 2);
	camera_comp2->setBackgroundColor(sf::Color::Black);
	camera_comp2->setScreenRect(0.5, 0.5, 0.5, 0.5); // set to half the screen size and placed in bottom right
	// only render player layer
	camera_comp2->setLayer("Player", true);
	camera_comp2->setLayer("Default", false);

	// background
	GameObject* background = scene_root->addChild(pref->InstantiatePrefab("P_RenderableObject", "Background"));
	Transform* background_transform = background->getTransform();
	background_transform->setLocalScale(5, 5);
	background_transform->setLocalZheight(-5);
	// set texture
	background->getComponent<Texture>()->setTexture("Backgrounds/Title_Screen");

	// test sound playing.
	AudioSystem::playSound("Folder_Test/Guitar");

	GameObject* animation_test = scene_root->addChild(std::make_unique<GameObject>("animation_test"));
	animation_test->getTransform()->setLocalScale(10, 10);
	animation_test->getTransform()->setLocalPosition(30, 30);

	animation_test->addComponent<Texture>();
	animation_test->addComponent<SpriteRenderer>();
	animation_test->setLayer("Player"); // set animation test to player layer.

	// add animations
	const auto animator = animation_test->addComponent<Animator>(std::vector<std::string>{
			"Player/Idle",
			"Player/Walk",
			"Player/Attack1",
			"Player/Attack2",
			"Player/Attack3",
			"Player/Jump",
			"Player/Cry",
			"Player/Die"
	});

	animator->playAnimation("Player/Idle"); // play animation

	GameObject* button = scene_root->addChild(pref->InstantiatePrefab("P_RenderableObject", "Button"));;
	button->addComponent<Clickable>();
	button->getTransform()->setGlobalScale(5, 5);
	button->getTransform()->setGlobalPosition(420, 400);
	button->addComponent<BoxCollider>(16, 13)->setPosition(3, 3);
	button->addScript<Button>()->addAnimatorTarget(animator);
}
