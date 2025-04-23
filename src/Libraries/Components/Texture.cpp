#include "Texture.h"
#include "../GameObject.h"
#include "SpriteRenderer.h"

Texture::Texture(std::string _path)
{
	tex_path = _path;
}

void Texture::start()
{
	setTexture(tex_path);
}

bool Texture::setTexture(std::string _path)
{
	if (game_object->hasComponent<SpriteRenderer>() && texture.loadFromFile(_path)) {
		game_object->getComponent<SpriteRenderer>()->getSprite()->setTexture(texture, true);
		return true;
	}
	return false;
}

bool Texture::setTexture(sf::Texture* _texture)
{
	if (game_object->hasComponent<SpriteRenderer>() && _texture != nullptr) {
		texture = *_texture;
		game_object->getComponent<SpriteRenderer>()->getSprite()->setTexture(texture, true);
		return true;
	}
	return false;
}

sf::Texture* Texture::getTexture()
{
	return &texture;
}
