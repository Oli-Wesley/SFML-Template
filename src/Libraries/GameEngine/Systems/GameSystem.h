#pragma once
#include "../GameObject.h"
#include <unordered_map>
#include "../Scene.h"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

class GameSystem
{
public:
	static GameSystem* get();
	void start();
	void start(std::string start_scene);
	void addScene(Scene* scene, std::string scene_name);
	void switchScene(std::string);
	void Remove(std::string scene_name);
	GameObject* findGameObject(std::string _id);
	void runGameLoop(float dt);

	void setTitle(std::string _title);
	void setResolution(sf::Vector2i res);
	void setResolution(int x, int y);
	void setFramerate(float framerate);
	void setPhysicsTimestep(float tickspersecond);

protected:
	static GameSystem* instance;

	// Scenes
	std::unordered_map<std::string, Scene*> scenes;
	std::string target_scene;
	Scene* currentScene;

	//window settings.
	sf::RenderWindow* window = nullptr;
	sf::Clock clock;
	sf::VideoMode resolution = sf::VideoMode(800, 600);
	std::string window_title = "Window";
	int framerate = 60;

	// physics system
	float accumulator = 0.0f;
	float physics_timestep = 1.0f / 60.0f; // 60Hz update

	// GameLoop, functions run in this order.
	void fixedUpdate(float dt);
	void runPhysics(float timestep); 
	void update(float dt);
	void lateUpdate(float dt);
	void render();
	void changeScene(); // changeScene last so objects can finish the update loop without breaking.

	// Delete copy constructor and assignment operator
	GameSystem() = default; // only allow creation of class within itself
	GameSystem(GameSystem const&) = delete;
	void operator=(GameSystem const&) = delete;
};