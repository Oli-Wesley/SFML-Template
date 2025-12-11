#include "Transform.h"
#include "../GameObject.h"
#include <cmath>

void Transform::setGlobalPosition(float _x, float _y)
{
	setGlobalPosition(sf::Vector2(_x, _y));
}

void Transform::setGlobalPosition(sf::Vector2f _position)
{
	if (game_object == nullptr || game_object->getParent() == nullptr) {
		setLocalPosition(_position);
	}
	else
	{
		sf::Vector2f parentGlobalPos = game_object->getParent()->getTransform()->getGlobalPosition();
		setLocalPosition(_position.x - parentGlobalPos.x, _position.y - parentGlobalPos.y);
	}
}


sf::Vector2f Transform::getGlobalPosition()
{
	// recursively from the root find the position.
	if (game_object->getParent() == nullptr) {
		return sf::Vector2f(position.x, position.y);
	}
	else {
		sf::Vector2f parent_global = game_object->getParent()->getTransform()->getGlobalPosition();
		sf::Vector2f this_local = getLocalPosition();
		return sf::Vector2f(this_local.x + parent_global.x, this_local.y + parent_global.y);
	}
}

sf::Vector2f Transform::getLocalPosition()
{
	sf::Vector2f parent_scale = game_object->getParent()->getTransform()->getGlobalScale();
	return sf::Vector2f(position.x * parent_scale.x, position.y * parent_scale.y);

}

void Transform::setLocalZheight(float _z)
{
	z_height = _z;
}

void Transform::setGlobalZheight(float _z)
{
	if (game_object == nullptr || game_object->getParent() == nullptr) {
		setLocalZheight(_z);
	}
	else
	{
		setLocalZheight(_z - game_object->getParent()->getTransform()->getGlobalZheight());
	}
}

float Transform::getLocalZheight()
{
	return z_height;
}

float Transform::getGlobalZheight()
{
	// recursively from the root find the position.
	if (game_object->getParent() == nullptr) {
		return float(z_height);
	}
	else {
		return getLocalZheight() + game_object->getParent()->getTransform()->getGlobalZheight();
	}
}

void Transform::setLocalPosition(float _x, float _y)
{
	setLocalPosition(sf::Vector2f(_x, _y));
}

void Transform::setLocalPosition(sf::Vector2f _position)
{
	position = _position;
}

void Transform::move(float _x, float _y)
{
	move(sf::Vector2f(_x, _y));
}

void Transform::move(sf::Vector2f _distance)
{
	// make sure distance is not 0
	if (sqrt(_distance.x * _distance.x + _distance.y * _distance.y) >= 0.0000000001)
		position += _distance;
}

void Transform::setGlobalScale(float _s)
{
	setGlobalScale(sf::Vector2f(_s, _s));
}

void Transform::setGlobalScale(float _s_x, float _s_y)
{
	setGlobalScale(sf::Vector2f(_s_x, _s_y));
}

void Transform::setGlobalScale(sf::Vector2f _scale)
{
	if (game_object == nullptr || game_object->getParent() == nullptr) {
		setLocalScale(_scale.x, _scale.y);
	}
	else
	{
		sf::Vector2f parentGlobalScale = game_object->getParent()->getTransform()->getGlobalScale();
		setLocalScale(_scale.x / parentGlobalScale.x, _scale.y / parentGlobalScale.y);
	}
}

sf::Vector2f Transform::getGlobalScale()
{
	if (game_object->getParent() == nullptr) {
		return scale;
	}
	else {
		sf::Vector2f parent_global = game_object->getParent()->getTransform()->getGlobalScale();
		return sf::Vector2f(scale.x * parent_global.x, scale.y * parent_global.y);
	}
}

sf::Vector2f Transform::getLocalScale()
{
	return scale;
}

void Transform::setLocalScale(float _s)
{
	setLocalScale(sf::Vector2f(_s, _s));
}

void Transform::setLocalScale(float _s_x, float _s_y)
{
	setLocalScale(sf::Vector2f(_s_x, _s_y));
}

void Transform::setLocalScale(sf::Vector2f _scale)
{
	scale = _scale;
}

void Transform::modifyScale(float _s_x, float _s_y)
{
	modifyScale(sf::Vector2f(_s_x, _s_y));
}

void Transform::modifyScale(sf::Vector2f _scale)
{
	sf::Vector2f current = getLocalScale();
	setLocalScale(current + _scale);
}

void Transform::rotateAroundPoint(float angle)
{
	rotateAroundPoint(angle, getGlobalPosition());
}

void Transform::rotateAroundPoint(float angle, sf::Vector2f point)
{
	sf::Vector2f globalPos = getGlobalPosition();
	float radians = angle * (3.14159265f / 180.0f);

	sf::Vector2f offset = globalPos - point;
	float rotatedX = offset.x * cos(radians) - offset.y * sin(radians);
	float rotatedY = offset.x * sin(radians) + offset.y * cos(radians);

	setGlobalPosition(point.x + rotatedX, point.y + rotatedY);
	setGlobalRotation(getGlobalRotation() + angle);
}

void Transform::setLocalRotation(float angle) { rotation = angle; }
float Transform::getLocalRotation() { return rotation; }

void Transform::setGlobalRotation(float angle)
{
	if (!game_object || !game_object->getParent()) {
		setLocalRotation(angle);
	}
	else {
		float parentGlobal = game_object->getParent()->getTransform()->getGlobalRotation();
		setLocalRotation(angle - parentGlobal);
	}
}

float Transform::getGlobalRotation()
{
	if (!game_object || !game_object->getParent())
		return rotation;
	return rotation + game_object->getParent()->getTransform()->getGlobalRotation();
}
