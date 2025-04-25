#pragma once
#include "IComponent.h"

class IScriptableBehaviour : public IComponent {
public:
	// other functions not defined by IComponent that scripts may need.
	virtual void fixedUpdate(float timestep) {}; // called at fixed intervals.
	virtual void onTriggerEnter(GameObject*) {}; // Called when entering a trigger.
	virtual void onTriggerStay(GameObject*) {}; // Called every frame inside a trigger.
	virtual void onTriggerExit(GameObject*) {}; // Called when exiting a trigger.
	virtual void onCollision(GameObject*) {};  // Called when colliding with another object.
};