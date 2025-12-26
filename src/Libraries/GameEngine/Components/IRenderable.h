#pragma once

#include "IComponent.h"
#include <SFML/Graphics.hpp>

// Any RenderableTypes inherit from this. (SpriteRenderer, TextRenderer ect...)
class IRenderable : public IComponent
{
public:
	virtual void render(sf::RenderTarget* window) = 0;
	virtual float getRenderOrder();
	virtual ~IRenderable() = default;
};
