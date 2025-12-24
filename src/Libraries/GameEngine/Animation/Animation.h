#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>

class Animation
{
public:
	enum STATE {
		PLAYING, 
		PAUSED, 
		STOPPED
	};

	Animation(std::string anim_id);
	~Animation();

	void updateAnimation(float dt); 
	sf::IntRect getCurrentFrameRect();
	bool canExitGracefully();
	std::string getTextureId();
	std::string getAnimationId();

	bool loadFromFile(std::string path);

	int getCurrentFrameCount();
	void setCurrentFrame(int frame_number);

	int getFramerate();
	void setFramerate(int fps); // Framerate in fps (60 = 60fps);

	void setLooping(bool should_loop);
	bool isLooping();

	STATE getState();
	void play(); // plays animation
	void pause(); // pauses animation, re-playing after pausing will remember which frame it was on
	void stop(); // stops animation, allowing to exit gracefully and forgetting which frame its on
	void restart(); // re-starts the animation

private:
	std::string animation_id; // name of the animation

	int framerate = 24;
	bool is_looping = false;

	sf::Vector2i texture_size = { 16,16 }; // size of each animation frame in the image. 
	sf::Vector2i start_position = { 0,0 }; // start position of the animation (if multiple animations are in the same texture)
	std::string texture_id = "";

	bool just_finished = false;
	float time_per_frame = 0.04166666666; // time per frame at 24fps.

	int current_frame = 0; // current frame of the animation
	int total_frames = 0; // total amount of frames
	float time = 0; // time of the animation. 
	STATE current_state = STOPPED;
}; 

