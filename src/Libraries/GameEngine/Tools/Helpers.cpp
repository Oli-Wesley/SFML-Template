#include "Helpers.h"

sf::FloatRect helpers::growRectToFit(const sf::FloatRect& a, const sf::FloatRect& b)
{
	float left = std::min(a.left, b.left);
	float top = std::min(a.top, b.top);
	float right = std::max(a.left + a.width, b.left + b.width);
	float bottom = std::max(a.top + a.height, b.top + b.height);

	return { left, top, right - left, bottom - top };
}
