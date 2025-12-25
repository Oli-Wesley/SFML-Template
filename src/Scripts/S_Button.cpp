#include "S_Button.h"
#include "../Libraries/GameEngine/GameObject.h"
#include "../Libraries/GameEngine/Systems/AudioSystem.h"
#include <random>
#include <algorithm>
#include <iostream>

void S_Button::start()
{
	tex_comp = game_object->getComponent<Texture>();
	click_comp = game_object->getComponent<Clickable>();
}

void S_Button::update(float dt)
{
	if (click_comp->isClicked()) {
		tex_comp->setTexture("UI/Desk_Button_Clicked");
		if (was_released) {
			was_released = false;
			std::random_device rd;
			std::mt19937 g(rd());
			std::vector<std::string> animations = animator_comp->getAllAnimationIds();
			std::shuffle(animations.begin(), animations.end(), g);
			if (animator_comp) animator_comp->playAnimation(animations[0], true);
			std::cout << "Playing Animation: " << animations[0] << "\n";
			AudioSystem::playSound("Buttons/Soft_Click");
		}
		return;
	}
	was_released = true;
	if (click_comp->isHovered())
	{
		tex_comp->setTexture("UI/Desk_Button_Hover");
	}
	else
	{
		tex_comp->setTexture("UI/Desk_Button_Idle");
	}
}

void S_Button::addAnimatorTarget(Animator* comp) {
	animator_comp = comp;
}
