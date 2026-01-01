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
	explicit Camera(sf::Vector2i size);
	struct CameraOutput
	{
		const sf::Texture* texture{};   // what to draw
		sf::FloatRect screen_rect;      // where on screen 
		int z_height = 0;                // draw order
	};

	void render(const std::vector<IRenderable*>& renderables); // take in a sorted list of all renderables and render it. 

	CameraOutput getRenderOutput() const;

	const std::unique_ptr<sf::View>& getView();
	void setViewArea(float width, float height);

	void setBackgroundColor(const sf::Color& color);
	sf::Color& getBackgroundColour();

	void setScreenRect(sf::FloatRect new_rect);
	void setScreenRect(float left, float top, float width, float height);

	sf::FloatRect getScreenRect() const;
	sf::FloatRect getScreenRectRelativeToWindow() const;

	void setTextureSize(sf::Vector2i size);
	sf::Vector2i getTextureSize() const;

	const sf::RenderTexture& getRenderTexture();

	sf::Vector2f convertScreenToWorld(sf::Vector2i pos);

	void setLayer(const std::string &layer_name,bool should_view);
	bool canSee(const GameObject *obj) const;

protected:
	sf::RenderTexture render_tex;
	std::unique_ptr<sf::View> view;
	sf::FloatRect screen_rect; // where to draw onto the window.
	sf::Color background_col = sf::Color::Transparent;
	float screen_z_height = 1.0f;

	uint32_t viewMask = 0; // Layer bitmask
};