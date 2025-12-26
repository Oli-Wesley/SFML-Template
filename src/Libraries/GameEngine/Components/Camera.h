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
		sf::FloatRect screen_rect;      // where on screen 
		int z_height = 0;                // draw order
	};

	void render(const std::vector<IRenderable*>& renderables); // take in a sorted list of all renderables and render it. 

	const CameraOutput getRenderOutput();

	const std::unique_ptr<sf::View>& getView();

	void setBackgroundColor(const sf::Color& color);
	sf::Color& getbackgroundColour();

protected:
	sf::RenderTexture render_tex;
	std::unique_ptr<sf::View> view;
	sf::FloatRect screenRect; // where to draw onto the window. 
	sf::Color background_col = sf::Color::Transparent;
};