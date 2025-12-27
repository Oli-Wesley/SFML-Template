#include "SpriteRenderer.h"
#include "../GameObject.h"
#include "Texture.h"
#include "Transform.h"

void SpriteRenderer::start()
{
	if (game_object->hasComponent<Texture>()) {
		sf::Texture tex = game_object->getComponent<Texture>()->getTexture();
		sprite.setTexture(tex);
	}
}

void SpriteRenderer::render(sf::RenderTarget* target)
{
	was_rendered = true;
	updateSprite();
	target->draw(sprite);
}

const sf::FloatRect SpriteRenderer::getGlobalBounds()
{
	updateSprite();
	return sprite.getGlobalBounds();
}

sf::Sprite& SpriteRenderer::getSprite()
{
	return sprite;
}

void SpriteRenderer::updateSprite()
{
	// update sprite position based onGameobject
	Transform* transform = game_object->getTransform();
	sprite.setPosition(transform->getGlobalPosition());
	sprite.setScale(transform->getGlobalScale());
	sprite.setRotation(transform->getGlobalRotation());
	sf::Vector2f scale = sprite.getScale();
}
