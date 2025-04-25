#pragma once
#include "../GameObject.h"
#include <unordered_map>
#include "../Scene.h"
#include <SFML/Graphics.hpp>

class GameSystem
{
public:
	static GameSystem* get();
	void start();
	void start(std::string start_scene);
	void Add(Scene* scene, std::string scene_name);
	void switchScene(std::string);
	void Remove(std::string scene_name);
	GameObject* findGameObject(std::string _id);
	void runGameLoop(float dt);

protected:
	static GameSystem* instance;

	// Scenes
	std::unordered_map<std::string, Scene*> scenes;
	std::string target_scene;
	Scene* currentScene;

	sf::RenderWindow* window = nullptr;
	sf::Clock clock;
	sf::VideoMode resolution = sf::VideoMode(800, 600);
	std::string window_title = "ComponentSystem";
	int framerate = 60;

	float accumulator = 0.0f;
	const float physics_timestep = 1.0f / 70.0f; // Fixed 70Hz update

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