#pragma once

#include "IRenderable.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"

class BoxCollider : public IRenderable
{
public:
	BoxCollider() = default;
	BoxCollider(int _x, int _y);
	// Position
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f);
	void setPosition(float _x, float _y);

	sf::FloatRect getCollider();

	// Size
	sf::Vector2f getSize();
	void setSize(sf::Vector2f);
	void setSize(float _x, float _y);

	// debug rendering
	void render(sf::RenderTarget* target) override;
	const sf::FloatRect getGlobalBounds() override;
	float getRenderOrder() override;

protected:
	// box Collider has a seperate position and size than transform, allowing it
	// to be offset and sized differently (it will still move and scale with the
	// transform.
	sf::Vector2f position = sf::Vector2f(0, 0);
	sf::Vector2f size = sf::Vector2f(10, 10);
};