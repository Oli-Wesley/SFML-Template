#pragma once

#include "../ComponentInterfaces/IComponent.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "SFML/Graphics/Text.hpp"

class TextRenderer; // Forward declaration

class TextComponent : public IComponent
{
public:
	TextComponent() = default;

	void setString(const std::string& str);
	void setFont(const std::string &path);
	void setCharacterSize(unsigned int size);
	void setFillColor(const sf::Color& color);
	void setStyle(sf::Text::Style style);

	const std::string& getString() const;
	sf::Font& getFont();
	unsigned int getCharacterSize() const;
	sf::Color getFillColor() const;
	sf::Text::Style getStyle() const;

private:
	void updateRenderer();

	std::string text;
	sf::Font font;
	unsigned int char_size = 10;
	sf::Color fillColor;
	sf::Text::Style textStyle = sf::Text::Style::Regular;
};