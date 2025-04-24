#include "IPhysicsObject.h"

void IPhysicsObject::applyForce(float _x, float _y)
{
	applyForce(sf::Vector2f(_x, _y));
}

void IPhysicsObject::applyForce(sf::Vector2f force)
{
	velocity += force;
}

void IPhysicsObject::setVelocity(float _x, float _y)
{
	setVelocity(sf::Vector2f(_x, _y));
}

void IPhysicsObject::setVelocity(sf::Vector2f val)
{
	velocity = val;
}

sf::Vector2f* IPhysicsObject::getVelocity()
{
	return &velocity;
}