#pragma once

#include "IComponent.h"
#include <SFML/Graphics/Texture.hpp>

class Texture : public IComponent
{
public:
	Texture() = default;
	// load a texture starting in the Textures folder without the file extension e,g (Player/Player_Default);
	Texture(std::string _path);
	void start() override;
	bool setTexture(std::string _path);
	// load a texture starting in the Textures folder without the file extension e,g (Player/Player_Default);
	bool setTexture(sf::Texture* _texture);
	sf::Texture* getTexture();

private:
	sf::Texture* texture;

	std::string tex_path = ""; // used to save data put in the constructor. then moved over during start.
};
