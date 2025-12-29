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
	Animator() = default;
	void start() override;

	explicit Animator(const std::string& anim_id);

	explicit Animator(const std::vector<std::string>& animation_ids);

	Animation &addAnimation(const std::string &anim_id);
	void addAnimation(const std::vector<std::string>& animation_ids);

	// returns true if animation played successfully;
	bool playAnimation(const std::string &animation_id);
	bool playAnimation(const std::string &animation_id, bool exit_gracefully);

	std::vector<std::string> getAllAnimationIds();
	Animation& getAnimation(const std::string &animationId);

	void update(float dt) override;


protected:
	void attemptChange();
	bool getComponents();
	std::pair<Animation*, bool> target_animation; // string = anim id, bool = exit gracefully
	Animation* current_animation = nullptr;
	std::unordered_map<std::string, Animation> animation_array;
	Texture* texture_component = nullptr;
	SpriteRenderer* sprite_component = nullptr;
};