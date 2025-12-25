#pragma once 
#include "../Libraries/GameEngine/ScriptableBehaviour.h" 
#include "../Libraries/GameEngine/Components.h"

class GameObject;

class S_Button : public ScriptableBehaviour {
public:
	void start() override;
	void update(float dt) override;

	void addAnimatorTarget(Animator* animator);

private:
	Texture* tex_comp = nullptr;
	Animator* animator_comp = nullptr;
	Clickable* click_comp = nullptr;
	bool was_released = true;
};