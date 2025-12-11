#include "SpriteRenderer.h"
#include "../GameObject.h"
#include "Texture.h"
#include "Transform.h"

void SpriteRenderer::render(sf::RenderWindow* target)
{
	// update sprite position based onGameobject
	Transform* transform = game_object->getTransform();
	sprite.setPosition(transform->getGlobalPosition());
	sprite.setScale(transform->getGlobalScale());
	sprite.setRotation(transform->getGlobalRotation());
	sf::Vector2f scale = sprite.getScale();
	target->draw(sprite);
}

sf::Sprite* SpriteRenderer::getSprite()
{
	return &sprite;
}
