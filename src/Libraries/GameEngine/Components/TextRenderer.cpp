#include "TextRenderer.h"
#include "../GameObject.h"
#include "Transform.h"
#include <cmath>

void TextRenderer::render(sf::RenderTarget* target)
{
	updateText();
	was_rendered = true;
	target->draw(text);
}

const sf::FloatRect TextRenderer::getGlobalBounds()
{
	updateText();
	return text.getGlobalBounds();
}

sf::Text* TextRenderer::getText()
{
	return &text;
}

void TextRenderer::updateText()
{
	// update text position based on GameObject
	text.setPosition(game_object->getTransform()->getGlobalPosition());

	// round to nearest int position so its not blurry 
	sf::Vector2f text_pos = text.getPosition();
	text.setPosition(
		std::round(text_pos.x),
		std::round(text_pos.y)
	);
	text.setCharacterSize(std::round(text_size * game_object->getTransform()->getGlobalScale().x));
}
