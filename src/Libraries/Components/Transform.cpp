#include "Transform.h"
#include "../GameObject.h"

void Transform::setGlobalPosition(float _x, float _y)
{
	if (attached_to == nullptr || attached_to->GetParent() == nullptr) {
		setLocalPosition(_x, _y);
	}
	else
	{
		sf::Vector2f parentGlobalPos = attached_to->GetParent()->GetComponent<Transform>().getGlobalPosition();
		setLocalPosition(_x - parentGlobalPos.x, _y - parentGlobalPos.y);
	}
}


sf::Vector2f Transform::getGlobalPosition()
{
	if (attached_to->GetParent() == nullptr) {
		return sf::Vector2f(x, y);
	}
	else {
		sf::Vector2f parent_global = attached_to->GetParent()->GetComponent<Transform>().getGlobalPosition();
		return sf::Vector2f(x + parent_global.x, y + parent_global.y);
	}
}

sf::Vector2f Transform::getLocalPosition()
{

	return sf::Vector2f(x, y);

}

void Transform::setLocalPosition(float _x, float _y)
{
	x = _x;
	y = _y;
}

void Transform::setGlobalScale(float _s_x, float _s_y)
{
	if (attached_to == nullptr || attached_to->GetParent() == nullptr) {
		setLocalScale(_s_x, _s_y);
	}
	else
	{
		sf::Vector2f parentGlobalScale = attached_to->GetParent()->GetComponent<Transform>().getGlobalScale();
		setLocalScale(_s_x / parentGlobalScale.x, _s_y / parentGlobalScale.y);
	}
}

sf::Vector2f Transform::getGlobalScale()
{
	if (attached_to->GetParent() == nullptr) {
		return sf::Vector2f(s_x, s_y);
	}
	else {
		sf::Vector2f parent_global = attached_to->GetParent()->GetComponent<Transform>().getGlobalScale();
		return sf::Vector2f(s_x * parent_global.x, s_y * parent_global.y);
	}
}

sf::Vector2f Transform::getLocalScale()
{
	return sf::Vector2f(s_x, s_y);
}

void Transform::setLocalScale(float _s_x, float _s_y)
{
	s_x = _s_x;
	s_y = _s_y;
}
