#include "Animator.h"
#include "../GameObject.h"
#include <iostream>

Animator::Animator()
{
}

Animator::Animator(Animation anim)
{
	addAnimation(anim);
}

Animator::Animator(std::vector<Animation> anims)
{
	addAnimation(anims);
}

// TODO: to assetDatabase:
void Animator::addAnimation(Animation anim)
{
	// TODO: some logic to check if anim actually exists. 
	animations.emplace(anim.getAnimationId(), anim);
}

// TODO: Move to assetDatabase:
void Animator::addAnimation(std::vector<Animation> anims)
{
	for (Animation anim : anims)
	{
		addAnimation(anim);
	}
}

bool Animator::playAnimation(std::string animation_id)
{
	return playAnimation(animation_id, false);
}

bool Animator::playAnimation(std::string animation_id, bool exit_gracefully)
{
	target_animation = { &animations.find(animation_id)->second, exit_gracefully };
	return true;
}

std::vector<std::string> Animator::getAllAnimationIds()
{
	std::vector<std::string> id;
	for (std::pair<const std::string, Animation>& anim : animations) {
		id.push_back(anim.first);
	}
	return id;
}

Animation& Animator::getAnimation(std::string animationId)
{
	return animations.at(animationId);
}

void Animator::update(float dt)
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
	// return if current is the same as target or target animation doesnt exist yet.
	if (current_animation == target_animation.first || !target_animation.first)
		return;

	// if should exit gracefully but cannot yet, return. (waiting untill it can)
	if (target_animation.second) {
		if (!current_animation->canExitGracefully())
			return;
	}

	if (current_animation)
		current_animation->stop();

	current_animation = target_animation.first;
	texture_component->setTexture(current_animation->getTextureId());
	current_animation->play();
	return;
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
