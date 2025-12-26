#include "Camera.h"
#include "../GameObject.h"
#include <iostream>

Camera::Camera(sf::Vector2i size)
{
	view = std::make_unique<sf::View>();
	view->setSize(size.x, size.y);
	screenRect.width = size.x;
	screenRect.height = size.y;
	render_tex.create(size.x, size.y);	
}

void Camera::render(const std::vector<IRenderable*>& renderables)
{
	// move view to transform position.
	view->setCenter(game_object->getTransform()->getGlobalPosition());
	render_tex.setView(*view);
	render_tex.clear(background_col);
	// render to texture.
	for (IRenderable* obj: renderables)
	{
		obj->render(&render_tex);
	}
	render_tex.display();
}

const Camera::CameraOutput Camera::getRenderOutput()
{
	CameraOutput output;
	output.texture = &render_tex.getTexture();
	output.screen_rect = screenRect;
	output.z_height = game_object->getTransform()->getLocalZheight(); // might move this to a camera specific variable as this is worldspace rather than screenspace.
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
