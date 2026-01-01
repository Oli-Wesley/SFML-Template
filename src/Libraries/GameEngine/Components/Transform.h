#pragma once

#include "IComponent.h"

#include "SFML/System/Vector2.hpp"

class Transform : public IComponent {
public:
	// Position
	void setGlobalPosition(float _x, float _y);
	void setGlobalPosition(sf::Vector2f _position);

	void setLocalPosition(float _x, float _y);
	void setLocalPosition(sf::Vector2f _position);

	void move(float _x, float _y);
	void move(sf::Vector2f _distance);

	// set origin relative to texture
	void setOrigin(float _x, float _y);
	void setOrigin(sf::Vector2f _origin);
	// set Origin to center of the gameObject (must be done once textures and such are added otherwise it won't work)
	void centerOrigin();
	sf::Vector2f getOrigin();

	sf::Vector2f getGlobalPosition();
	// set position of the top left (ignoring rotations)
	void setGlobalTopLeft(sf::Vector2f _topLeft);

	sf::Vector2f getLocalPosition() const;

	// Zheight is used for render order
	void setLocalZheight(float _z);
	void setGlobalZheight(float _z);
	float getLocalZheight();
	float getGlobalZheight();

	// Scale
	// if only given 1 value, assume uniform scaling
	void setGlobalScale(float _s);
	void setGlobalScale(float _s_x, float _s_y);
	void setGlobalScale(sf::Vector2f _scale);

	void setLocalScale(float _s);
	void setLocalScale(float _s_x, float _s_y);
	void setLocalScale(sf::Vector2f _scale);

	void modifyScale(float _s_x, float _s_y);
	void modifyScale(sf::Vector2f _scale);

	sf::Vector2f getGlobalScale();
	sf::Vector2f getLocalScale();

	// ROTATIONS: I have no idea how all this works, so thanks mr gpt (rare AI usage)
	void rotateAroundPoint(float angle, sf::Vector2f point); // rotate around a specified point
	void rotateAroundPoint(float angle); // defaults to top left corner.
	void rotateAroundCenter(float angle);

	float getLocalRotation();
	void setLocalRotation(float angle);

	float getGlobalRotation();
	void setGlobalRotation(float angle);
protected:
	sf::Vector2f position = sf::Vector2f(0, 0);
	sf::Vector2f origin = sf::Vector2f(0, 0);
	float z_height = 0; // order in render queue (if 0 parent is drawn above) 
	sf::Vector2f scale = sf::Vector2f(1, 1);
	float rotation = 0.f;
};