#include "RigidBody.h"
#include "../GameObject.h"
#include <cmath>
void RigidBody::physicsUpdate(float timestep)
{
	// if isnt static, run physics ticks.
	if (!is_static)
	{
		// make sure timestep cant be NAN
		if (!std::isfinite(timestep) || timestep <= 0.0f)
		{
			return;
		}

		velocity.y += gravity_force * timestep;

		// make sure air resitence isnt NAN
		if (!std::isfinite(air_resistance))
		{
			air_resistance = 0.0f; // fail-safe
		}

		float drag = 1.0f - air_resistance * timestep;
		drag = std::clamp(drag, 0.0f, 1.0f);

		velocity *= drag;

		// if anything does become infinite, set it back to 0
		if (!std::isfinite(velocity.x))
			velocity.x = 0.0f;
		if (!std::isfinite(velocity.y))
			velocity.y = 0.0f;

		game_object->getTransform()->move(velocity * timestep);
	}
}
