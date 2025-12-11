#pragma once
class GameObject;

class ScriptableBehaviour {
public:
	virtual ~ScriptableBehaviour() = default;
	void addGameObject(GameObject* obj) { game_object = obj; };
	// SCRIPTABLE BEHAVIOUR
	// lifecycle stuff.
	virtual void start() {}    // Called once when the script is created.
	virtual void onEnable() {} // Called when the component is enabled
	virtual void update(float dt) {}     // Called every frame
	virtual void lateUpdate(float dt) {} // called after update
	virtual void onDisable() {}          // Called when the GameObject is disabled 
	virtual void onDestroy() {}          // Called when the component is destroyed
	virtual void fixedUpdate(float timestep) {}; // called at fixed intervals. (physics tick)

	// Physics stuff.
	virtual void onTriggerEnter(GameObject*) {}; // Called when entering a trigger.
	virtual void onTriggerStay(GameObject*) {};  // Called every frame inside a trigger.
	virtual void onTriggerExit(GameObject*) {};  // Called when exiting a trigger.
	virtual void onCollision(GameObject*) {};    // Called when colliding with another object.

	// Clickable stuff (needs clickable component)
	virtual void onClick() {};     // Called when this object is clicked
	virtual void onRelease() {};   // Called when mouse released on object
	virtual void onHover() {};     // Called when mouse hovers over object
	virtual void onStopHover() {}; // called once when mouse leaves collider

protected:
	GameObject* game_object; // useful for accessing other components on the gameObject. such as rotation or scale.
};