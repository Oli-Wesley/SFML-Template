#include "TextComponent.h"
#include "../GameObject.h"
#include "TextRenderer.h"
#include "../Tools/AssetDatabase.h"
#include <memory>

void TextComponent::setString(const std::string& str)
{
	text = str;
	updateRenderer();
}

void TextComponent::setFont(const std::string &path)
{
	font = AssetDatabase::getFont(path);
}

void TextComponent::setCharacterSize(const unsigned int size)
{
	char_size = size;
	updateRenderer();
}

void TextComponent::setFillColor(const sf::Color& color)
{
	fillColor = color;
	updateRenderer();
}

void TextComponent::setStyle(const sf::Text::Style style)
{
	textStyle = style;
	updateRenderer();
}

const std::string& TextComponent::getString() const
{
	return text;
}
sf::Font& TextComponent::getFont() 
{
	return font;
}
unsigned int TextComponent::getCharacterSize() const
{
	return char_size;
}
sf::Color TextComponent::getFillColor() const
{
	return fillColor;
}
sf::Text::Style TextComponent::getStyle() const
{
	return textStyle;
}

void TextComponent::updateRenderer()
{
	auto* renderer = game_object->getComponent<TextRenderer>();
	if (!renderer)
		return;

	sf::Text* renderText = renderer->getText();
	renderText->setString(text);
	renderText->setFont(font);
	renderer->text_size = char_size;
	renderText->setFillColor(fillColor);
	renderText->setStyle(textStyle);
}