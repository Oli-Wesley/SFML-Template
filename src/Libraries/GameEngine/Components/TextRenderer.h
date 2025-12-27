#pragma once

#include "IRenderable.h"
#include <SFML/Graphics/Text.hpp>

class TextRenderer : public IRenderable
{
public:
	void render(sf::RenderTarget* target) override;
	const sf::FloatRect getGlobalBounds() override;

	sf::Text* getText();
	int text_size = 10;
private:
	sf::Text text;
	void updateText();
};