#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <algorithm>


namespace helpers {
    sf::FloatRect growRectToFit(const sf::FloatRect& a, const sf::FloatRect& b);
}