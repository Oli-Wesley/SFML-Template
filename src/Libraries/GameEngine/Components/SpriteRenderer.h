#pragma once

#include "IRenderable.h"

class SpriteRenderer : public IRenderable {

public:
	void render(sf::RenderWindow* target) override;
	sf::Sprite* getSprite();	

private:
	sf::Sprite sprite; // texture for sprite stored elsewhere in another component (either animator or static sprite);
};