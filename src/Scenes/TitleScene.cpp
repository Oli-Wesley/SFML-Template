#include "TitleScene.h"
#include "../Libraries/GameEngine.h"
#include "../Scripts/S_Button.h"

void TitleScene::load()
{
	PrefabRegistry* pref = PrefabRegistry::get();
	scene_background_color = sf::Color(255, 0, 255);

	GameObject* camera = scene_root->addChild(std::make_unique<GameObject>("Camera"));
	Camera* camera_comp = camera->addComponent<Camera>(sf::Vector2i(960, 540));
	camera->getTransform()->setGlobalPosition(960/2, 540/2); // set to middle of screen (0,0 = top left);
	camera_comp->setScreenRect(sf::IntRect(0,0,480, 270)); // set to half the screen size

	// setup second camera (exact same view, just different screen position)
	GameObject* camera2 = scene_root->addChild(std::make_unique<GameObject>("Camera"));
	Camera* camera_comp2 = camera2->addComponent<Camera>(sf::Vector2i(960, 540));
	camera2->getTransform()->setGlobalPosition(960 / 2, 540 / 2); // set to middle of screen (0,0 = top left)
	camera_comp2->setScreenRect(sf::IntRect(480, 270, 480, 270)); // set to half the screen size

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

	// example of loading from variable if needed (its also possible to make animations entirely through code, though bulky and silly)
	Animation baby_anim = Animation("Baby/Cry");
	baby_anim.setSpeed(2);  // example editing of values 

	// add animations
	Animator* animator = animation_test->addComponent<Animator>(std::vector<Animation>{
		Animation("Player/Idle"),
			Animation("Player/Walk"),
			Animation("Player/Attack1"),
			Animation("Player/Attack2"),
			Animation("Player/Attack3"),
			Animation("Player/Jump"),
			Animation("Player/Cry"),
			Animation("Player/Die"),
			Animation("Baby/Drink"),
			Animation("Baby/Idle"),
			Animation("Baby/Poop"),
			Animation("Baby/Sit"),
			Animation("Baby/Walk"),
			baby_anim // give animator animation by variable 
	});

	animator->playAnimation("Player/Idle"); // play animation

	GameObject* button = scene_root->addChild(pref->InstantiatePrefab("P_RenderableObject", "Button"));;
	button->addComponent<Clickable>();
	button->getTransform()->setGlobalScale(5, 5);
	button->getTransform()->setGlobalPosition(420, 400);
	button->addComponent<BoxCollider>(16, 13)->setPosition(3, 3);
	button->addScript<S_Button>()->addAnimatorTarget(animator);
}
