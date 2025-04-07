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

protected:
	float x = 0, y = 0;
};