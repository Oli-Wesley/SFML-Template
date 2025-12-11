#pragma once 
#include "Clickable.h"

class Draggable : public Clickable {
public:
	void update(float dt) override;
	bool isHeld() { return is_held; };
private:
	sf::Vector2f relative_mouse_pos;
	bool is_held = false;
};