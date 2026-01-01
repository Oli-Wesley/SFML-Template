#include "BoxCollider.h"
#include "../GameObject.h"
#include "../Systems/GameSystem.h"
#include "RigidBody.h"

BoxCollider::BoxCollider(int _x, int _y)
{
	setSize(sf::Vector2f(_x, _y));
}

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
	sf::Vector2f pos =
		game_object->getTransform()->getGlobalPosition() + position; // pos
	sf::Vector2f scale = sf::Vector2f(
		game_object->getTransform()->getGlobalScale().x * size.x,
		game_object->getTransform()->getGlobalScale().y * size.y); // size
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

void BoxCollider::render(sf::RenderTarget* target)
{
	if (GameSystem::get()->isDebug())
	{	
		was_rendered = true;
		// i think this is quite expensive to do every frame, but like its debug so idc
		sf::RectangleShape rect = sf::RectangleShape(
			sf::Vector2f(getCollider().width, getCollider().height));
		rect.setPosition({ getCollider().left, getCollider().top });
		rect.setFillColor(sf::Color::Transparent);
		if (game_object->hasComponent<RigidBody>())
		{
			if (game_object->getComponent<RigidBody>()->is_trigger)
				rect.setOutlineColor(sf::Color::Blue);
			else
				rect.setOutlineColor(sf::Color::Red);
		}
		else
			rect.setOutlineColor(sf::Color::Green);

		rect.setOutlineThickness(-2);
		rect.setFillColor(sf::Color(255, 0, 255, 32));
		target->draw(rect);
	}
}

sf::FloatRect BoxCollider::getGlobalBounds()
{
	return getCollider(); // just return collider here. 
}

sf::FloatRect BoxCollider::getLocalBounds() {
	return getCollider(); // just return here, just used for keeping compiler happy.
}

float BoxCollider::getRenderOrder()
{
	// returns the renderOrder, used for sorting the render_queue so elements get
	// drawn in the correct order. (forces this to be very high, so debug boxes
	// are always drawn on top.

	return game_object->getTransform()->getGlobalZheight() + 10000.0f;
}

bool BoxCollider::checkIntersection(BoxCollider *collider) {
	const sf::FloatRect a_rect = getCollider();
	const sf::FloatRect b_rect = collider->getCollider();

	return (
		a_rect.left < b_rect.left + b_rect.width &&
		a_rect.left + a_rect.width > b_rect.left &&
		a_rect.top < b_rect.top + b_rect.height &&
		a_rect.top + a_rect.height > b_rect.top);
}
