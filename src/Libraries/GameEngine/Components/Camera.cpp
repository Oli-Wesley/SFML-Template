#include "Camera.h"
#include "../GameObject.h"
#include "../Systems/GameSystem.h"
#include <iostream>

#include "../Tools/LayerManager.h"

Camera::Camera(const sf::Vector2i size)
{
	view = std::make_unique<sf::View>();
	view->setSize(size.x, size.y);
	screen_rect.width = size.x; // default screen_rect to same size as texture;
	screen_rect.height = size.y;
	render_tex.create(size.x, size.y);
	setLayer("Default", true); // default render layer
}

void Camera::render(const std::vector<IRenderable*>& renderables)
{
	// move view to transform position.
	view->setCenter(game_object->getTransform()->getGlobalPosition());
	render_tex.setView(*view);
	render_tex.clear(background_col);

	const sf::FloatRect viewBounds(view->getCenter().x - view->getSize().x / 2.f,
		view->getCenter().y - view->getSize().y / 2.f,
		view->getSize().x,
		view->getSize().y);

	// render to texture.
	for (IRenderable* obj : renderables)
	{
		obj->resetBeforeRender(); // reset was_rendered
		if (obj->getGlobalBounds().intersects(viewBounds) && canSee(obj->getGameObject()))
			obj->render(&render_tex); // render to a texture.
	}
	render_tex.display();
}

Camera::CameraOutput Camera::getRenderOutput() const {
	CameraOutput output;
	output.texture = &render_tex.getTexture();
	output.screen_rect = getScreenRectRelativeToWindow();
	output.z_height = screen_z_height; // might move this to a camera specific variable as this is worldspace rather than screenspace
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

sf::Color& Camera::getBackgroundColour()
{
	return background_col;
}

void Camera::setScreenRect(const sf::FloatRect new_rect)
{
	screen_rect = new_rect;
}

void Camera::setScreenRect(const float left, const float top, const float width, const float height)
{
	setScreenRect(sf::FloatRect(left, top, width, height));
}

sf::FloatRect Camera::getScreenRect() const {
	return screen_rect;
}

sf::FloatRect Camera::getScreenRectRelativeToWindow() const {
	const sf::Vector2u window_size = GameSystem::get()->getWindow()->getSize();
	const sf::FloatRect rect = getScreenRect();
	sf::FloatRect return_rect;

	return_rect.left = rect.left * window_size.x;
	return_rect.width = rect.width * window_size.x;
	return_rect.top = rect.top * window_size.y;
	return_rect.height = rect.height * window_size.y;

	return return_rect;
}


void Camera::setTextureSize(const sf::Vector2i size)
{
	render_tex.create(size.x, size.y);
}

sf::Vector2i Camera::getTextureSize() const {
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
	const sf::RenderWindow* window = GameSystem::get()->getWindow();

	// Mouse in window pixels
	const sf::Vector2f mousePixel = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	// Camera screen rectangle (pixels)
	const sf::FloatRect rect = getScreenRectRelativeToWindow();

	// Reject if mouse is outside camera's area on screen
	if (!rect.contains(
		static_cast<float>(mousePixel.x),
		static_cast<float>(mousePixel.y)))
	{
		return { -1.f, -1.f }; // invalid
	}

	// Convert window pixel to camera view pixel (area relative to it on screen)
	sf::Vector2i cameraPixel;
	cameraPixel.x = static_cast<int>(mousePixel.x - rect.left);
	cameraPixel.y = static_cast<int>(mousePixel.y - rect.top);

	// Scale to render texture resolution
	const sf::Vector2i texSize = getTextureSize();
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

void Camera::setLayer(const std::string &layer_name, const bool should_view) {

	// special case for setting view to all, or none;
	if (layer_name == "ALL") {
		if (should_view)
			viewMask = 0xFFFFFFFF; // sets everything to 1
		else
			viewMask = 0; // sets everything to 0
		return;
	}

	const int target_id = LayerManager::getLayerIndex(layer_name);
	if (target_id == -1)
		return;

	if (should_view) {
		viewMask |= (1U << target_id);  // Set bit at index to 1 for layer is rendered by camera
	} else {
		viewMask &= ~(1U << target_id); // Set bit at index to 0 for layer is rendered by camera
	}
}

bool Camera::canSee(const GameObject* obj) const {
		return (viewMask & (1U << obj->getLayer())) != 0; // if bit at the index given is 1
	}
