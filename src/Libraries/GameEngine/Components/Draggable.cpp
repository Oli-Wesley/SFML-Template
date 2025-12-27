#include "Draggable.h"
#include "../Systems/GameSystem.h"

void Draggable::update(float dt)
{
	Clickable::update(dt); // call clickable update

	// I THINK THIS WILL BREAK IF DRAGGING BETWEEN 2 CAMERAS, TODO: test and fix
	std::vector<Camera*> cameras = GameSystem::get()->getCurrentScene()->getAllCameras();
	for (Camera* cam : cameras)
	{
		sf::Vector2f mouse_pos = cam->convertScreenToWorld(sf::Mouse::getPosition(*GameSystem::get()->getWindow()));
		if (mouse_pos == sf::Vector2f(-1.f, -1.f))
			continue;

		// was clicked this frame.
		if (!was_mouse_pressed && is_mouse_pressed) {
			sf::Vector2f object_pos = game_object->getTransform()->getGlobalPosition();
			relative_mouse_pos = sf::Vector2f(object_pos.x - mouse_pos.x, object_pos.y - mouse_pos.y);
		}

		// set is held to true if clicking within the hitbox.
		if (is_mouse_pressed && is_hovering && !was_mouse_pressed)
			is_held = true;

		// set is held to false when the mouse is released (not when is_hovering is false because that can happen if the mouse is moved too fast)
		else if (!is_mouse_pressed && is_held)
			is_held = false;

		// if being held, set the position + the relative mouse position. 
		if (is_held)
			game_object->getTransform()->setGlobalPosition(mouse_pos.x + relative_mouse_pos.x, mouse_pos.y + relative_mouse_pos.y);
	}
}
