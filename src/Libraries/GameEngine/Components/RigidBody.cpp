#include "RigidBody.h"
#include "../GameObject.h"
void RigidBody::physicsUpdate(float timestep)
{
	// Basic physics, does not care about friction or air resistance yet. friction will need to be done elsewhere, TODO: air resistance will be done here 
	if (!is_static && !is_trigger) {
		velocity.y += gravity_force * timestep;

		float drag = 1.0f - air_resistance * timestep;
		drag = std::clamp(drag, 0.0f, 1.0f); // ensure it can't move backwards, or add force accidentally...
		velocity *= drag;

		game_object->getTransform()->move(velocity * timestep);
	}
}
