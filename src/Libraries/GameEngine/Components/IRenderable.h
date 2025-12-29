#pragma once

#include "IComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>

// Any RenderableTypes inherit from this. (SpriteRenderer, TextRenderer ect...)
class IRenderable : public IComponent
{
public:
	virtual void render(sf::RenderTarget* target) = 0;
	virtual sf::FloatRect getGlobalBounds() = 0;
	virtual float getRenderOrder();

	virtual  ~IRenderable() override = default;
	void resetBeforeRender();

	bool wasRenderedLastFrame() const;

protected:
	bool was_rendered = false;
};
