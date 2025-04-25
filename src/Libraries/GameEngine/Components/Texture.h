#pragma once

#include "IComponent.h"
#include <SFML/Graphics/Texture.hpp>

class Texture : public IComponent
{
public:
	Texture() = default;
	Texture(std::string _path);
	void start() override;
	bool setTexture(std::string _path);
	bool setTexture(sf::Texture* _texture);
	sf::Texture* getTexture();
	
private:
	sf::Texture texture;
	std::string tex_path = "";
};

