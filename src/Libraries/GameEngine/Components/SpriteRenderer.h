#pragma once

#include "IRenderable.h"
#include <SFML/Graphics/Sprite.hpp>

class SpriteRenderer : public IRenderable
{
public:
	void start() override;
	void render(sf::RenderTarget* target) override;
	const sf::FloatRect getGlobalBounds() override;
	sf::Sprite& getSprite();


	
private:
	sf::Sprite sprite; // texture for sprite stored elsewhere in another component
	// (either animator or static sprite);
	void updateSprite();
};