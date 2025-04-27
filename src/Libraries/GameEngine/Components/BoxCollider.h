#pragma once

#include "IRenderable.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Rect.hpp"

class BoxCollider : public IRenderable {
public:
    bool is_trigger = false ;
    BoxCollider() = default;
    BoxCollider(bool debug) { is_debug_drawn = debug; };
    // Position
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f);
    void setPosition(float _x, float _y);

    sf::FloatRect getCollider();

    // Size
    sf::Vector2f getSize();
    void setSize(sf::Vector2f);
    void setSize(float _x, float _y);

    // debug rendering
    void render(sf::RenderWindow* window) override;
    float getRenderOrder() override;
protected:

    // box Collider has a seperate position and size than transform, allowing it to be offset and sized differently (it will still move and scale with the transform.
    sf::Vector2f position = sf::Vector2f(0, 0);
    sf::Vector2f size = sf::Vector2f(10, 10);
    // flag for drawing collider hitboxes
    
    // TODO: MOVE DEBUG TO GAMESYSTEM AS A FLAG THERE.
    bool is_debug_drawn = false;
};