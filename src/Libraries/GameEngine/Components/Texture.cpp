#include "Texture.h"
#include "../GameObject.h"
#include "SpriteRenderer.h"
#include "../Tools/AssetDatabase.h"

Texture::Texture(std::string _path)
{
	tex_path = _path;
}

void Texture::start()
{
	if (tex_path != "")
		setTexture(tex_path);
}

// TODO: move this to the new assetDatabase system
bool Texture::setTexture(std::string _path)
{
	return setTexture(AssetDatabase::getTexture(_path));
}

bool Texture::setTexture(sf::Texture* _texture)
{
	if (game_object->hasComponent<SpriteRenderer>() && _texture != nullptr)
	{
		texture = _texture;
		game_object->getComponent<SpriteRenderer>()->getSprite()->setTexture(*texture, true);
		return true;
	}
	return false;
}

sf::Texture* Texture::getTexture()
{
	return texture;
}
