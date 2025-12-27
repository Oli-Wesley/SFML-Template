#include "Camera.h"
#include "../GameObject.h"
#include "../Systems/GameSystem.h"
#include <iostream>

Camera::Camera(sf::Vector2i size)
{
	view = std::make_unique<sf::View>();
	view->setSize(size.x, size.y);
	screen_rect.width = size.x; // default screen_rect to same size as texture;
	screen_rect.height = size.y;
	render_tex.create(size.x, size.y);
}

void Camera::render(const std::vector<IRenderable*>& renderables)
{
	// move view to transform position.
	view->setCenter(game_object->getTransform()->getGlobalPosition());
	render_tex.setView(*view);
	render_tex.clear(background_col);

	sf::FloatRect viewBounds(view->getCenter().x - view->getSize().x / 2.f,
		view->getCenter().y - view->getSize().y / 2.f,
		view->getSize().x,
		view->getSize().y);

	// render to texture.
	for (IRenderable* obj : renderables)
	{
		obj->resetBeforeRender(); // reset was_rendered
		if (obj->getGlobalBounds().intersects(viewBounds))
			obj->render(&render_tex); // rended to a texture. 
	}
	render_tex.display();
}

const Camera::CameraOutput Camera::getRenderOutput()
{
	CameraOutput output;
	output.texture = &render_tex.getTexture();
	output.screen_rect = getScreenRectRelativeToWindow();
	output.z_height = screen_z_height; // might move this to a camera specific variable as this is worldspace rather than screenspace.
	return output;
}

const std::unique_ptr<sf::View>& Camera::getView()
{
	return view;
}

void Camera::setBackgroundColor(const sf::Color& color)
{
	background_col = color;
}

sf::Color& Camera::getbackgroundColour()
{
	return background_col;
}

void Camera::setScreenRect(sf::FloatRect new_rect)
{
	screen_rect = new_rect;
}

void Camera::setScreenRect(float left, float top, float width, float height)
{
	setScreenRect(sf::FloatRect(left, top, width, height));
}

const sf::FloatRect Camera::getScreenRect()
{
	return screen_rect;
}

const sf::FloatRect Camera::getScreenRectRelativeToWindow() {
	sf::Vector2u window_size = GameSystem::get()->getWindow()->getSize();
	sf::FloatRect rect = getScreenRect();
	sf::FloatRect return_rect;

	return_rect.left = rect.left * window_size.x;
	return_rect.width = rect.width * window_size.x;
	return_rect.top = rect.top * window_size.y;
	return_rect.height = rect.height * window_size.y;

	return return_rect;
}


void Camera::setTextureSize(sf::Vector2i size)
{
	render_tex.create(size.x, size.y);
}

sf::Vector2i Camera::getTextureSize()
{
	sf::Vector2i size;
	size.x = render_tex.getSize().x;
	size.y = render_tex.getSize().y;
	return size;
}

const sf::RenderTexture& Camera::getRenderTexture()
{
	return render_tex;
}

sf::Vector2f Camera::convertScreenToWorld(sf::Vector2i pos)
{
	sf::RenderWindow* window = GameSystem::get()->getWindow();

	// Mouse in window pixels
	sf::Vector2f mousePixel = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	// Camera screen rectangle (pixels)
	sf::FloatRect rect = getScreenRectRelativeToWindow();

	// Reject if mouse is outside camera's area on screen
	if (!rect.contains(
		static_cast<float>(mousePixel.x),
		static_cast<float>(mousePixel.y)))
	{
		return { -1.f, -1.f }; // invalid
	}

	// Convert window pixel to camera view pixel (area realtive to it on screen)
	sf::Vector2i cameraPixel;
	cameraPixel.x = static_cast<int>(mousePixel.x - rect.left);
	cameraPixel.y = static_cast<int>(mousePixel.y - rect.top);

	// Scale to render texture resolution
	sf::Vector2i texSize = getTextureSize();
	cameraPixel.x = static_cast<int>(
		cameraPixel.x * (texSize.x / rect.width)
		);
	cameraPixel.y = static_cast<int>(
		cameraPixel.y * (texSize.y / rect.height)
		);

	// Map through the camera view
	sf::Vector2f worldPos =
		getRenderTexture().mapPixelToCoords(cameraPixel, *getView());

	sf::Vector2f coords;
	coords.x = worldPos.x;
	coords.y = worldPos.y;

	return coords;
}