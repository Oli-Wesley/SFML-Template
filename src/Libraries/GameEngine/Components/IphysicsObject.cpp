#include "IPhysicsObject.h"

void IPhysicsObject::applyForce(const float _x, const float _y)
{
	applyForce(sf::Vector2f(_x, _y));
}

void IPhysicsObject::applyForce(const sf::Vector2f force)
{
	velocity += force;
}

void IPhysicsObject::setVelocity(const float _x, const float _y)
{
	setVelocity(sf::Vector2f(_x, _y));
}

void IPhysicsObject::setVelocity(const sf::Vector2f val)
{
	velocity = val;
}

sf::Vector2f* IPhysicsObject::getVelocity()
{
	return &velocity;
}