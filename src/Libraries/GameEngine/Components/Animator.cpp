#include "Animator.h"
#include "../GameObject.h"

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

void Animator::addAnimation(Animation anim)
{
	animations.emplace(anim.getAnimationId(), anim);
}

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
	// TODO: some logic to check if anim actually exists. 
	target_animation = {&animations.find(animation_id)->second, exit_gracefully};
	return true;
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
	// if should exit gracefully but cannot, return instantly;
	if (target_animation.first && target_animation.second) {
		if (!target_animation.first->canExitGracefully())
			return;
	}

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
