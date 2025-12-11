#pragma once

#pragma once

#include "../GameObject.h"
#include "BoxCollider.h"
#include "IComponent.h"
#include "IScriptableBehaviour.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Clickable : public IComponent
{
public:
	void update(float dt) override;
	void lateUpdate(float dt) override;

	bool isClicked();
	bool isHovered();

protected:
	bool was_hovered;
	bool was_mouse_pressed = 1;
	bool is_hovering;
	bool is_mouse_pressed;
	bool checkPointCol(sf::FloatRect bounds, sf::Vector2f _pos);
	sf::Vector2f getMousePos();
};