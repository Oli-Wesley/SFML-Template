#include "Clickable.h"
#include "../Systems/GameSystem.h"

void Clickable::update(float dt)
{
	BoxCollider* collider = game_object->getComponent<BoxCollider>();
	// if any of the needed components dont exist, return.
	if (!game_object->isActive() || collider == nullptr)
		return;

	sf::Vector2f mouse_pos = getMousePos();

	is_hovering = checkPointCol(collider->getCollider(), mouse_pos);
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
	return is_hovering;
}

bool Clickable::checkPointCol(sf::FloatRect bounds, sf::Vector2f _pos)
{
	return (
		bounds.left <= _pos.x && _pos.x <= bounds.left + bounds.width &&
		bounds.top <= _pos.y && _pos.y <= bounds.top + bounds.height);
}

sf::Vector2f Clickable::getMousePos()
{
	sf::RenderWindow* window = GameSystem::get()->getWindow();
	return window->mapPixelToCoords(sf::Mouse::getPosition(*window));

}
