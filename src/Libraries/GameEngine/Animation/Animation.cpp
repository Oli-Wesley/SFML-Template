#include "Animation.h"
#include "../Tools/AssetDatabase.h"
#include "../Tools/FileParser.h"

Animation::Animation(std::string anim_id) : 
	animation_id(anim_id)
{
	loadFromFile(anim_id);
}

Animation::~Animation()
{
}

void Animation::updateAnimation(float dt)
{
	if (current_state != STATE::PLAYING)
		return;

	just_finished = false;
	time += dt;

	int new_frame = static_cast<int>(time / time_per_frame);

	if (new_frame >= total_frames)
	{
		just_finished = true;

		if (is_looping)
		{
			// preserve leftover time for smooth looping
			time -= total_frames * time_per_frame;
			current_frame = static_cast<int>(time / time_per_frame);
		}
		else
		{
			current_frame = total_frames - 1;
			current_state = STATE::STOPPED;
		}
	}
	else
	{
		current_frame = new_frame;
	}
}

sf::IntRect Animation::getCurrentFrameRect()
{
	return sf::IntRect(
		start_position.x + std::min(current_frame, total_frames - 1) * texture_size.x,
		start_position.y,
		texture_size.x,
		texture_size.y);
}

bool Animation::canExitGracefully()
{
	return just_finished || current_state == STATE::STOPPED; // if stopped or just finished reset.
}

std::string Animation::getTextureId()
{
	return texture_id;
}

std::string Animation::getAnimationId()
{
	return animation_id;
}

// path relative to the Animations folder with extensions removed 
bool Animation::loadFromFile(std::string path)
{
	path = "../Data/Animations/" + path + ".anim";
	FileParser file;
	if (file.loadFromFile(path));

	std::string animation_id; // name of the animation

	setFramerate(file.getValue<int>("framerate", framerate));
	setLooping(file.getValue<bool>("loop", is_looping));
	texture_id = file.getValue<std::string>("texture_id", "");
	texture_size = file.getValue<sf::Vector2i>("texture_size", texture_size); // size of each animation frame in the image. 
	start_position = file.getValue<sf::Vector2i>("start_position", start_position);
	total_frames = file.getValue<int>("frame_count", 0);

	return true;
}

int Animation::getCurrentFrameCount()
{
	return current_frame;
}

void Animation::setCurrentFrame(int frame_number)
{
	if (frame_number <= total_frames)
		current_frame = frame_number;
	else if (frame_number < 0)
		current_frame = 0;
	else
		current_frame = total_frames;
}

int Animation::getFramerate()
{
	return framerate;
}

void Animation::setFramerate(int fps)
{
	framerate = fps;
	time_per_frame = 1.0f / static_cast<float>(fps); // seconds per frame.  

}

void Animation::setLooping(bool should_loop)
{
	is_looping = should_loop;
}

bool Animation::isLooping()
{
	return is_looping;
}

Animation::STATE Animation::getState()
{
	return current_state;
}

void Animation::play()
{
	current_state = Animation::STATE::PLAYING;
}

void Animation::pause()
{
	current_state = Animation::STATE::PAUSED;
}

void Animation::stop()
{
	current_state = Animation::STATE::STOPPED;
	current_frame = 0;
	time = 0;
}

void Animation::restart()
{
	stop();
	play();
}
