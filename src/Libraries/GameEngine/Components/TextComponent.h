#pragma once

#include "IComponent.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

class TextRenderer; // Forward declaration

class TextComponent : public IComponent
{
public:
	TextComponent() = default;

	void setString(const std::string& str);
	void setFont(std::unique_ptr<sf::Font>& font);
	void setFont(std::string path);
	void setCharacterSize(unsigned int size);
	void setFillColor(const sf::Color& color);
	void setStyle(sf::Text::Style style);

	const std::string& getString() const;
	sf::Font* getFont() const;
	unsigned int getCharacterSize() const;
	sf::Color getFillColor() const;
	sf::Text::Style getStyle() const;

private:
	void updateRenderer();

	std::string text;
	std::unique_ptr<sf::Font> font;
	unsigned int charSize;
	sf::Color fillColor;
	sf::Text::Style textStyle;
};