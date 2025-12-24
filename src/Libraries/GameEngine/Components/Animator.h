#pragma once
#include "IComponent.h"
#include <unordered_map>
#include <string>
#include "../Animation/Animation.h"
#include "Texture.h"
#include "SpriteRenderer.h"

class Animator : public IComponent
{
public:
	Animator();
	Animator(Animation anim);
	Animator(std::vector<Animation> anims);
	
	void addAnimation(Animation anim);
	void addAnimation(std::vector<Animation> anims);

	bool playAnimation(std::string animation_id);
	bool playAnimation(std::string animation_id, bool exit_gracefully);

	void update(float dt) override;


protected:
	void attemptChange();
	bool getComponents();
	std::pair<Animation*, bool> target_animation; // string = anim id, bool = exit gracefully
	Animation* current_animation = nullptr;
	std::unordered_map<std::string, Animation> animations;
	Texture* texture_component = nullptr;
	SpriteRenderer* sprite_component = nullptr;
};