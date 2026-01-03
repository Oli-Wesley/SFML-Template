#include "Transform.h"
#include "../GameObject.h"
#include <cmath>

void Transform::setGlobalPosition(const float _x, const float _y)
{
	setGlobalPosition(sf::Vector2(_x, _y));
}

void Transform::setGlobalPosition(const sf::Vector2f _position)
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

void Transform::setOrigin(float _x, float _y) {
	setOrigin({_x, _y});
}

void Transform::setOrigin(sf::Vector2f _origin) {
	origin = _origin;
}

void Transform::centerOrigin() {
	sf::FloatRect bounds = game_object->getLocalBounds();
	setOrigin({bounds.width / 2.0f, bounds.height / 2.0f});
}

sf::Vector2f Transform::getOrigin() {
	return origin;
}

sf::Vector2f Transform::getGlobalPosition()
{
	// recursively from the root find the position.
	if (game_object->getParent() == nullptr) {
		return {position.x, position.y};
	}
	else {
		sf::Vector2f parent_global = game_object->getParent()->getTransform()->getGlobalPosition();
		sf::Vector2f this_local = getLocalPosition();
		return {this_local.x + parent_global.x, this_local.y + parent_global.y};
	}
}

void Transform::setGlobalTopLeft(const sf::Vector2f _topLeft) {
	sf::FloatRect currentBounds = game_object->getGlobalBoundsWithChildren();

	float deltaX = _topLeft.x - currentBounds.left;
	float deltaY = _topLeft.y - currentBounds.top;

	sf::Vector2f currentPos = getGlobalPosition();

	setGlobalPosition(currentPos.x + deltaX, currentPos.y + deltaY);
}

sf::Vector2f Transform::getLocalPosition() const {
	return position;
}

void Transform::setLocalZheight(const float _z)
{
	z_height = _z;
}

void Transform::setGlobalZheight(const float _z)
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

void Transform::setLocalPosition(const float _x, const float _y)
{
	setLocalPosition(sf::Vector2f(_x, _y));
}

void Transform::setLocalPosition(const sf::Vector2f _position)
{
	position = _position;
}

void Transform::move(const float _x, const float _y)
{
	move(sf::Vector2f(_x, _y));
}

void Transform::move(const sf::Vector2f _distance)
{
	// make sure distance is not 0
	if (sqrt(_distance.x * _distance.x + _distance.y * _distance.y) >= 0.0000000001)
		position += _distance;
}

void Transform::setGlobalScale(const float _s)
{
	setGlobalScale(sf::Vector2f(_s, _s));
}

void Transform::setGlobalScale(float _s_x, float _s_y)
{
	setGlobalScale(sf::Vector2f(_s_x, _s_y));
}

void Transform::setGlobalScale(const sf::Vector2f _scale)
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
		return {scale.x * parent_global.x, scale.y * parent_global.y};
	}
}

sf::Vector2f Transform::getLocalScale()
{
	return scale;
}

void Transform::setLocalScale(const float _s)
{
	setLocalScale(sf::Vector2f(_s, _s));
}

void Transform::setLocalScale(const float _s_x, const float _s_y)
{
	setLocalScale(sf::Vector2f(_s_x, _s_y));
}

void Transform::setLocalScale(const sf::Vector2f _scale)
{
	scale = _scale;
}

void Transform::modifyScale(const float _s_x, const float _s_y)
{
	modifyScale(sf::Vector2f(_s_x, _s_y));
}

void Transform::modifyScale(const sf::Vector2f _scale)
{
	sf::Vector2f current = getLocalScale();
	setLocalScale(current + _scale);
}

void Transform::rotateAroundPoint(const float angle)
{
	rotateAroundPoint(angle, getGlobalPosition());
}

void Transform::rotateAroundCenter(const float angle) {
	sf::Vector2f oldOrigin = origin;
	sf::FloatRect bounds = game_object->getLocalBounds();
	sf::Vector2f newOrigin = {bounds.width / 2.0f, bounds.height / 2.0f};

	// Set the new origin
	origin = newOrigin;

	// Compensate position so the object doesn't jump
	sf::Vector2f diff = newOrigin - oldOrigin;
	float rad = getGlobalRotation() * (3.14159265f / 180.0f);
	float rx = diff.x * std::cos(rad) - diff.y * std::sin(rad);
	float ry = diff.x * std::sin(rad) + diff.y * std::cos(rad);

	move(rx, ry);
	setGlobalRotation(angle);
}

void Transform::rotateAroundPoint(const float angle, const sf::Vector2f point)
{
	sf::Vector2f globalPos = getGlobalPosition();
	float radians = angle * (3.14159265f / 180.0f);

	const sf::Vector2f offset = globalPos - point;

	float cosA = std::cos(radians);
	float sinA = std::sin(radians);

	float rotatedX = offset.x * cosA - offset.y * sinA;
	float rotatedY = offset.x * sinA + offset.y * cosA;

	// Apply the shift
	setGlobalPosition(point.x + rotatedX, point.y + rotatedY);
	setGlobalRotation(getGlobalRotation() + angle);
}

void Transform::setLocalRotation(float angle) { rotation = angle; }
float Transform::getLocalRotation() { return rotation; }

void Transform::setGlobalRotation(const float angle)
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
