#include "Button.h"
#include "../../Libraries/GameEngine/GameObject.h"
#include "../../Libraries/GameEngine/Systems/AudioSystem.h"
#include <random>
#include <algorithm>
#include <iostream>

void Button::start() {
    tex_comp = game_object->getComponent<Texture>();
    click_comp = game_object->getComponent<Clickable>();
}

void Button::update(float dt) {
    if (click_comp->isClicked()) {
        tex_comp->setTexture("UI/Desk_Button_Clicked");
        if (was_released) {
            was_released = false;
            std::random_device rd;
            std::mt19937 g(rd());
            if (animator_comp) {
                std::vector<std::string> animations = animator_comp->getAllAnimationIds();
                std::ranges::shuffle(animations, g);
                animator_comp->playAnimation(animations[0], true);
                std::cout << "Playing Animation: " << animations[0] << "\n";
            }
            AudioSystem::playSound("Buttons/Soft_Click");
        }
        return;
    }
    was_released = true;
    if (click_comp->isHovered()) {
        tex_comp->setTexture("UI/Desk_Button_Hover");
    } else {
        tex_comp->setTexture("UI/Desk_Button_Idle");
    }
}

void Button::addAnimatorTarget(Animator *animator) {
    animator_comp = animator;
}
