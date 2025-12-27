#pragma once
#include <SFML/Graphics/Color.hpp>
#include "SFML/System/Vector2.hpp"
#include <memory>
#include <vector>
#include "Components/Camera.h"
// prototype gameObject so it is happy at compile time.
class GameObject;

class Scene
{
public:
	Scene();
	~Scene();
	std::unique_ptr<GameObject> scene_root = nullptr; // Empty GameObject at 0,0 where everything starts
	// from.
	std::unique_ptr<GameObject> dont_destroy = nullptr;

	std::unique_ptr<GameObject> unload(); // Returns Game Objects with Persistance between scenes
	// (and their childeren)

	virtual void load(std::unique_ptr<GameObject> dont_destroy);

	sf::Color getSceneColor() { return scene_background_color; };

	void onWindowResize(sf::Vector2i new_size);

	// take in a list of renderables and render them to every camera in that order.
	std::vector<Camera::CameraOutput> render();

	std::vector<Camera*> getAllCameras();

protected:
	virtual void load() = 0; // Every scene needs a load function.
	virtual void onUnload() {};

	// std::vector<std::unique_ptr<Camera>> cameras;
	
	// background of the window if nothing is rendered there. (cameras store their own background colour) 
	sf::Color scene_background_color = sf::Color(0,0,0);

	sf::Vector2i target_resolution = sf::Vector2i(960, 540);
};