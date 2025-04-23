#pragma once

#include <SFML/Graphics.hpp>
#include "IComponent.h"

// Any RenderableTypes inherit from this. (SpriteRenderer, TextRenderer ect...)
class IRenderable : public IComponent {
public:
    virtual void render(sf::RenderWindow& window) = 0;
    float getRenderOrder();
    virtual ~IRenderable() = default;
};
