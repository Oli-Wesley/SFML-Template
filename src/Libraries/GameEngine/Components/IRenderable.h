#pragma once

#include "IComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>

// Any RenderableTypes inherit from this. (SpriteRenderer, TextRenderer ect...)
class IRenderable : public IComponent
{
public:
	virtual void render(sf::RenderTarget* target) = 0;
	virtual const sf::FloatRect getGlobalBounds() = 0;
	virtual float getRenderOrder();
	virtual ~IRenderable() = default;
	void resetBeforeRender();
	const bool wasRenderedLastFrame();

protected:
	bool was_rendered = false;
};
