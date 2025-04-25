#pragma once

#include "IComponent.h"
#include <iostream>
#include "SFML/System/Vector2.hpp"

class Transform : public IComponent {
public:

	// passing into 2 seperate x and y floats just converts to vector2f then calls the same function there.

	// Position
	void setGlobalPosition(float _x, float _y);
	void setGlobalPosition(sf::Vector2f _position);

	void setLocalPosition(float _x, float _y);
	void setLocalPosition(sf::Vector2f _position);

	void move(float _x, float _y);
	void move(sf::Vector2f _distance);

	sf::Vector2f getGlobalPosition();
	sf::Vector2f getLocalPosition();

	// Zheight is used for render unorder TODO: USE IT IN RENDER ORDER.
	void setLocalZheight(float _z);
	void setGlobalZheight(float _z);
	float getLocalZheight();
	float getGlobalZheight();



	// Scale
	void setGlobalScale(float _s_x, float _s_y);
	void setGlobalScale(sf::Vector2f _scale);

	void setLocalScale(float _s_x, float _s_y);
	void setLocalScale(sf::Vector2f _scale);

	void modifyScale(float _s_x, float _s_y);
	void modifyScale(sf::Vector2f _scale);

	sf::Vector2f getGlobalScale();
	sf::Vector2f getLocalScale();

protected:
	sf::Vector2f position = sf::Vector2f(0, 0);
	float z_height = 0; // order in render queue (if 0 parent is drawn above) TODO: USE THIS.
	sf::Vector2f scale = sf::Vector2f(1, 1);
};