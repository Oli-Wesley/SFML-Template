#include "Animator.h"
#include "../GameObject.h"
#include <ranges>

#include "../Tools/AssetDatabase.h"
#include "SFML/System/String.hpp"

void Animator::start() {
	addAnimation("EngineCore/Missing_Animation");
}

Animator::Animator(const std::string &anim_id)
{
	addAnimation(anim_id);
}

Animator::Animator(const std::vector<std::string> &animation_ids) {
	addAnimation(animation_ids);
}

Animation &Animator::addAnimation(const std::string &anim_id) {
	Animation new_animation = AssetDatabase::getAnimation(anim_id);
	animation_array.insert({anim_id, new_animation});
	return getAnimation(anim_id);
}

void Animator::addAnimation(const std::vector<std::string> &animation_ids) {
	for (sf::String animation : animation_ids)
	{
		addAnimation(animation);
	}
}

bool Animator::playAnimation(const std::string &animation_id)
{
	return playAnimation(animation_id, false);
}

bool Animator::playAnimation(const std::string &animation_id, bool exit_gracefully)
{
	if (animation_array.contains(animation_id)) {
		target_animation = { &animation_array.find(animation_id)->second, exit_gracefully };
		return true;
	}

	playAnimation("EngineCore/Missing_Animation");
	return false;
}

std::vector<std::string> Animator::getAllAnimationIds()
{
	std::vector<std::string> ids;
	for (const auto &key: animation_array | std::views::keys) {
		if (key != "EngineCore/Missing_Animation") // dont return default missing animation.
			ids.push_back(key);
	}
	return ids;
}

Animation& Animator::getAnimation(const std::string &animationId)
{
	return animation_array.at(animationId);
}

void Animator::update(const float dt)
{
	// if cant find either texture or sprite component return.
	if (!getComponents())
		return;
	// if components exist, attempt to change
	attemptChange();

	if (!current_animation)
		return;
	// update animation and change textures rect. 
	current_animation->updateAnimation(dt);
	sprite_component->getSprite().setTextureRect(current_animation->getCurrentFrameRect());
}

void Animator::attemptChange()
{
	// return if current is the same as target or target animation doesn't exist yet.
	if (current_animation == target_animation.first || !target_animation.first)
		return;

	// if should exit gracefully but cannot yet, return. (waiting until it can)
	if (current_animation && target_animation.second) {
		if (!current_animation->canExitGracefully())
			return;
	}

	if (current_animation)
		current_animation->stop();

	current_animation = target_animation.first;
	texture_component->setTexture(current_animation->getTextureId());
	current_animation->play();
}

bool Animator::getComponents()
{
	// insta return if already existing
	if (texture_component && sprite_component)
		return true;

	// fetch components 
	if (!texture_component)
		texture_component = game_object->getComponent<Texture>();

	if (!sprite_component)
		sprite_component = game_object->getComponent<SpriteRenderer>();

	// check again
	if (texture_component && sprite_component)
		return true;
	return false;
}
