#include "SpriteRenderer.h"
#include "Transform.h"
#include "../GameObject.h"

void SpriteRenderer::render(sf::RenderWindow& target)
{
	// update sprite position based onGameobject
	sprite.setPosition(game_object->getTransform()->getGlobalPosition());
	sprite.setScale(game_object->getTransform()->getGlobalScale());
	
	target.draw(sprite);
}
