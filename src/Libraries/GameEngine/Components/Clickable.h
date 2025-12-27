#pragma once

#pragma once

#include "../GameObject.h"
#include "BoxCollider.h"
#include "IComponent.h"
#include "IScriptableBehaviour.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Camera.h"

class Clickable : public IComponent
{
public:
	void update(float dt) override;
	void lateUpdate(float dt) override;

	bool isClicked();
	bool isHovered();

protected:
	bool was_hovered = 0;
	bool was_mouse_pressed = 0;
	bool is_hovering = 0;
	bool is_mouse_pressed = 0;
	bool checkPointCol(sf::FloatRect bounds, sf::Vector2f _pos);
};