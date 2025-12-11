#pragma once
#include "IComponent.h"
#include "../ScriptableBehaviour.h"
#include <memory>

class IScriptableBehaviour : public IComponent {
private:
	// array of all scripts on a gameObject.
	std::vector<std::unique_ptr<ScriptableBehaviour>> scripts;
public:
	virtual ~IScriptableBehaviour() {
		for (std::unique_ptr<ScriptableBehaviour>& s : scripts) {
			s->onDestroy(); 
		}
		scripts.clear();
	}

	void addScript(std::unique_ptr<ScriptableBehaviour> script) {
		script->addGameObject(game_object);
		script->start();
		scripts.push_back(std::move(script));
	}

	template<typename T>
	T* getScript() {
		for (std::unique_ptr<ScriptableBehaviour>& script : scripts) {
			if (auto casted = dynamic_cast<T*>(script.get()))
				return casted;
		}
		return nullptr;
	}

	// all functions that are scriptable. 
	// Called when the component is enabled
	void onEnable() override { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->onEnable(); }
	// Called every frame
	void update(float dt) override { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->update(dt); }
	// called after update
	void lateUpdate(float dt) override { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->lateUpdate(dt); }
	// Called when the GameObject is disabled 
	void onDisable() override { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->onDisable(); }
	// Called when the component is destroyed
	void onDestroy() override { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->onDestroy(); }
	// called at fixed intervals. (physics tick)
	void fixedUpdate(float timestep) { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->fixedUpdate(timestep); }

	// Physics stuff.
	// Called when entering a trigger.
	void onTriggerEnter(GameObject* obj) { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->onTriggerEnter(obj); }
	// Called every frame inside a trigger.
	void onTriggerStay(GameObject* obj) { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->onTriggerStay(obj); }
	// Called when exiting a trigger.
	void onTriggerExit(GameObject* obj) { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->onTriggerExit(obj); }
	// Called when colliding with another object.
	void onCollision(GameObject* obj) { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->onCollision(obj); }

	// Clickable stuff (needs clickable component)
	// Called when this object is clicked
	void onClick() { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->onClick(); }
	// Called when mouse released on object
	void onRelease() { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->onRelease(); }
	// Called when mouse hovers over object
	void onHover() { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->onHover(); }
	// called once when mouse leaves collider
	void onStopHover() { for (std::unique_ptr<ScriptableBehaviour>& s : scripts) s->onStopHover(); }
};
