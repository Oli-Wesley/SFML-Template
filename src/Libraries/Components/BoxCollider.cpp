#include "BoxCollider.h"
#include "../GameObject.h"

sf::Vector2f BoxCollider::getPosition()
{
	return position;
}

void BoxCollider::setPosition(sf::Vector2f val)
{
	position = val;
}

void BoxCollider::setPosition(float _x, float _y)
{
	setPosition(sf::Vector2(_x, _y));
}

sf::FloatRect BoxCollider::getCollider()
{
	// calculate global position relative to transform
	sf::Vector2f pos = game_object->getTransform()->getGlobalPosition() + position; // pos 
	sf::Vector2f scale = sf::Vector2f(game_object->getTransform()->getGlobalScale().x * size.x, game_object->getTransform()->getGlobalScale().y * size.y);  // size 
	return sf::FloatRect(pos.x, pos.y, scale.x, scale.y);
}

sf::Vector2f BoxCollider::getSize()
{
	return size;
}

void BoxCollider::setSize(sf::Vector2f val)
{
	size = val;
}

void BoxCollider::setSize(float _x, float _y)
{
	setSize(sf::Vector2(_x, _y));
}

void BoxCollider::render(sf::RenderWindow* window)
{
	if (is_debug_drawn) {
		// this is quite expensive to do every frame, but like its debug so idc 
		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(getCollider().width, getCollider().height));
		rect.setPosition({getCollider().left, getCollider().top });
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(-2);
		window->draw(rect);
	}
}
