#include "TitleScene.h"
#include "../Libraries/GameEngine.h"

void TitleScene::load()
{
	PrefabRegistry* pref = PrefabRegistry::get();
	scene_background_color = sf::Color(255, 0, 255);

	// background
	GameObject* background = scene_root->addChild(std::make_unique<GameObject>("background"));
	Transform* background_transform = background->getTransform();
	background_transform->setLocalPosition(0, 0);
	background_transform->setLocalScale(5, 5);
	background_transform->setLocalZheight(-5);

	// setup rendering
	background->addComponent<SpriteRenderer>();
	background->addComponent<Texture>("Backgrounds/Title_Screen");

	// test sound playing.
	AudioSystem::playSound("Folder_Test/Guitar");

	GameObject* animation_test = scene_root->addChild(std::make_unique<GameObject>("animation_test"));
	animation_test->getTransform()->setLocalScale(10, 10);
	animation_test->getTransform()->setLocalPosition(30, 30);

	animation_test->addComponent<Texture>();
	animation_test->addComponent<SpriteRenderer>();

	// add animations
	Animator* animator = animation_test->addComponent<Animator>(std::vector<Animation>{
		Animation("Player/Idle"),
		Animation("Player/Walk"),
		Animation("Player/Baby")
	});


	animator->playAnimation("Player/Idle");
}
