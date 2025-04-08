#pragma once

#include "IComponent.h"
#include <iostream>
#include "SFML/System/Vector2.hpp"

class Transform : public IComponent {
public:
	// Position
	void setGlobalPosition(float _x, float _y);
	sf::Vector2f getGlobalPosition();
	sf::Vector2f getLocalPosition();
	void setLocalPosition(float _x, float _y);

	// Scale
	void setGlobalScale(float _s_x, float _s_y);
	sf::Vector2f getGlobalScale();
	sf::Vector2f getLocalScale();
	void setLocalScale(float _s_x, float _s_y);

protected:
	float x = 0, y = 0;
	float s_x = 1, s_y = 1;
};