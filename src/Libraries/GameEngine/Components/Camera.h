#pragma once
#include "IComponent.h"
#include "IRenderable.h"
#include "Transform.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <memory>

class Camera : public IComponent {
public:
	Camera(sf::Vector2i size);
	struct CameraOutput
	{
		const sf::Texture* texture;   // what to draw
		sf::IntRect screen_rect;      // where on screen 
		int z_height = 0;                // draw order
	};

	void render(const std::vector<IRenderable*>& renderables); // take in a sorted list of all renderables and render it. 

	const CameraOutput getRenderOutput();

	const std::unique_ptr<sf::View>& getView();

	void setBackgroundColor(const sf::Color& color);
	sf::Color& getbackgroundColour();

	void setScreenRect(sf::IntRect new_rect);
	const sf::IntRect getScreenRect();

	void setTextureSize(sf::Vector2i size);
	sf::Vector2i getTextureSize();

	const sf::RenderTexture& getRenderTexture();

	sf::Vector2f convertScreenToWorld(sf::Vector2i pos);
	

protected:
	sf::RenderTexture render_tex;
	std::unique_ptr<sf::View> view;
	sf::IntRect screen_rect; // where to draw onto the window. 
	sf::Color background_col = sf::Color::Transparent;
	float screen_z_height = 1.0f;
};