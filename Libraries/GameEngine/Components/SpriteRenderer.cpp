#include "SpriteRenderer.h"
#include "../GameObject.h"
#include "Texture.h"
#include "Transform.h"

void SpriteRenderer::start()
{
	if (game_object->hasComponent<Texture>()) {
		const sf::Texture tex = game_object->getComponent<Texture>()->getTexture();
		sprite.setTexture(tex);
	}
}

void SpriteRenderer::render(sf::RenderTarget* target)
{
	was_rendered = true;
	updateSprite();
	target->draw(sprite);
}

sf::FloatRect SpriteRenderer::getGlobalBounds()
{
	updateSprite();
	return sprite.getGlobalBounds();
}

sf::FloatRect SpriteRenderer::getLocalBounds() {
	return sprite.getLocalBounds();
}

sf::Sprite& SpriteRenderer::getSprite()
{
	return sprite;
}

void SpriteRenderer::updateSprite()
{
	// update sprite position based on Game object
	Transform* transform = game_object->getTransform();
	sprite.setOrigin(transform->getOrigin());
	sprite.setPosition(transform->getGlobalPosition());
	sprite.setScale(transform->getGlobalScale());
	sprite.setRotation(transform->getGlobalRotation());
	sf::Vector2f scale = sprite.getScale();
}
