#include "Texture.h"
#include "../GameObject.h"
#include "SpriteRenderer.h"
#include "../Tools/AssetDatabase.h"

Texture::Texture(const std::string &_path)
{
	tex_path = _path;
}

void Texture::start()
{
	if (!tex_path.empty())
		setTexture(tex_path);
}

bool Texture::setTexture(const std::string &_path)
{
	return setTexture(AssetDatabase::getTexture(_path));
}

bool Texture::setTexture(const sf::Texture &_texture)
{
	if (game_object->hasComponent<SpriteRenderer>())
	{
		texture = _texture;
		game_object->getComponent<SpriteRenderer>()->getSprite().setTexture(texture, true);
		return true;
	}
	return false;
}

sf::Texture& Texture::getTexture()
{
	return texture;
}
