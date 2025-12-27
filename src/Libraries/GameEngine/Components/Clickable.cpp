#include "Clickable.h"
#include "Camera.h"
#include "../Systems/GameSystem.h"

void Clickable::update(float dt)
{	
	isHovered(); // check if is hovered

	is_mouse_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	// Hover enter
	if (is_hovering && !was_hovered)
	{
		for (auto* comp : game_object->getAllComponents())
		{
			if (auto* script = dynamic_cast<IScriptableBehaviour*>(comp))
			{
				script->onHover();
			}
		}
	}

	// Hover exit
	if (!is_hovering && was_hovered)
	{
		for (auto* comp : game_object->getAllComponents())
		{
			if (auto* script = dynamic_cast<IScriptableBehaviour*>(comp))
			{
				script->onStopHover();
			}
		}
	}

	// Click
	if (is_hovering && !was_mouse_pressed && is_mouse_pressed)
	{
		for (auto* comp : game_object->getAllComponents())
		{
			if (auto* script = dynamic_cast<IScriptableBehaviour*>(comp))
			{
				script->onClick();
			}
		}
	}

	// Release
	if (was_mouse_pressed && !is_mouse_pressed && is_hovering)
	{
		for (auto* comp : game_object->getAllComponents())
		{
			if (auto* script = dynamic_cast<IScriptableBehaviour*>(comp))
			{
				script->onRelease();
			}
		}
	}
}

void Clickable::lateUpdate(float dt)
{
	// update on late update so childeren can actually check if it was just pressed on this frame.
	was_hovered = is_hovering;
	was_mouse_pressed = is_mouse_pressed;
}

bool Clickable::isClicked()
{
	return (is_hovering && is_mouse_pressed);
}

bool Clickable::isHovered()
{
	BoxCollider* collider = game_object->getComponent<BoxCollider>();
	// if any of the needed components dont exist, return.
	if (!game_object->isActive() || collider == nullptr)
		return false; 

	std::vector<Camera*> cameras = GameSystem::get()->getCurrentScene()->getAllCameras();

	is_hovering = false;

	for (Camera* cam : cameras) {
		// get mouse pos and convert to screen space
		sf::Vector2f mouse_pos = cam->convertScreenToWorld(sf::Mouse::getPosition(*GameSystem::get()->getWindow()));
		// check its valid
		if (mouse_pos == sf::Vector2f(-1.f, -1.f))
			continue;
		// set hovering if hovering.
		else if (checkPointCol(collider->getCollider(), mouse_pos))
			is_hovering = true;
	}
	return is_hovering;
}

bool Clickable::checkPointCol(sf::FloatRect bounds, sf::Vector2f _pos)
{
	return (
		bounds.left <= _pos.x && _pos.x <= bounds.left + bounds.width &&
		bounds.top <= _pos.y && _pos.y <= bounds.top + bounds.height);
}