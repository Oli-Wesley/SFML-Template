#pragma once

#include "IRenderable.h"
#include <SFML/Graphics/Text.hpp>

class TextRenderer : public IRenderable
{
public:
	void render(sf::RenderTarget* target) override;
	sf::Text* getText();
	int text_size = 10;
private:
	sf::Text text;
};