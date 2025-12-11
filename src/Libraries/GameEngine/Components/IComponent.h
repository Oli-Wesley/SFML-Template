#pragma once

// prototype gameObject so it is happy at compile time.
class GameObject;

class IComponent
{
public:
	virtual ~IComponent() {
		onDestroy();
	}

	virtual void start() {}    // Called once when the GameObject is first enabled
	virtual void onEnable() {} // Called when the component is enabled
	virtual void update(float dt) {}     // Called every frame
	virtual void lateUpdate(float dt) {} // called after update
	virtual void onDisable() {}          // Called when the GameObject is disabled
	virtual void onDestroy() {}          // Called when the component is destroyed

	void setGameObject(GameObject* _game_object) { game_object = _game_object; };

protected:
	GameObject* game_object = nullptr;
};
