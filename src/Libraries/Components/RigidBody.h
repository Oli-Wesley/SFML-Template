#pragma once 

#include "IPhysicsObject.h"
#include "SFML/System/Vector2.hpp"


class RigidBody : public IPhysicsObject 
{
public:

	void physicsUpdate(float dt) override;
	bool is_static = false;
	float friction = 1.0f;
	float mass = 1.0f;
	float bouncyness = 0.1f;
	float air_resistance = 0.0f;


protected:

};