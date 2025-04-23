#include "RigidBody.h"
#include "../GameObject.h"
void RigidBody::physicsUpdate(float dt)
{
	// Basic physics, does not care about friction or air resistance yet. friction will need to be done elsewhere, TODO: air resistance will be done here 
	velocity.y += gravity_force * dt;
	game_object->getTransform()->move(velocity);
}
