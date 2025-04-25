#pragma once

#include <SFML/System/Vector2.hpp>
#include "IComponent.h"

class IPhysicsObject : public IComponent {
public:
	virtual void physicsUpdate(float dt) = 0;

	virtual void applyForce(float _x, float _y);
	virtual void applyForce(sf::Vector2f);
	virtual void setVelocity(float _x, float _y);
	virtual void setVelocity(sf::Vector2f);
	virtual sf::Vector2f* getVelocity();
protected:

	sf::Vector2f velocity;
	float air_resistance = 0.1f;
	// MOVE GRAVITY FORCE TO SOME SORT OF GAMEINFO (10 is pulled from my ass so may be wrong);
	float gravity_force = 700;

};