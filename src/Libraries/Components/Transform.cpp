#include "Transform.h"
#include "../GameObject.h"

void Transform::setGlobalPosition(float _x, float _y)
{
	
		if (attatched_to->GetParent() == nullptr) {
			x = _x;
			y = _y;
		}
		else
		{
			x = _x + attatched_to->GetComponent<Transform>().getGlobalPosition().x;
			y = _y + attatched_to->GetComponent<Transform>().getGlobalPosition().y;
		}
	
}

sf::Vector2f Transform::getGlobalPosition()
{
	// if has parent, add parents position to current one
	if (attatched_to->GetParent() != nullptr) {
		sf::Vector2 parentPos = attatched_to->GetParent()->GetComponent<Transform>().getGlobalPosition();
		return sf::Vector2f(x + parentPos.x, y + parentPos.y);
	}
	// else return this position as it doesnt have parents. 
	return getLocalPosition();
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
