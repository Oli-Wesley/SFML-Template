#include "GameSystem.h"
#include "PhysicsSystem.h"
#include "../Scene.h"


// Define the static member variable
GameSystem* GameSystem::instance = nullptr;

GameSystem* GameSystem::get()
{
	if (instance == nullptr)
	{
		instance = new GameSystem();
	}
	return instance;
}

void GameSystem::start()
{
	window = new sf::RenderWindow(resolution, window_title);
	window->setFramerateLimit(framerate);

	clock.restart();

	while (window->isOpen()) {
		sf::Event e;
		while (window->pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window->close();
		}
		runGameLoop(clock.restart().asSeconds()); // pass time since last frame as dt to the current gameLoop.
	}
}

void GameSystem::start(std::string start_scene)
{
	switchScene(start_scene);
	changeScene();
	start();
}

void GameSystem::Add(Scene* scene, std::string scene_name)
{
	scenes.emplace(scene_name, scene);
}

void GameSystem::switchScene(std::string scene_name)
{
	target_scene = scene_name;
}

void GameSystem::Remove(std::string scene_name)
{
	scenes.erase(scene_name);
}

GameObject* GameSystem::findGameObject(std::string _id)
{
	return nullptr;
}

void GameSystem::runGameLoop(float dt)
{
	fixedUpdate(dt); // physics called in here aswell.
	update(dt);
	lateUpdate(dt);
	render();
	changeScene();
}

void GameSystem::runPhysics(float timestep)
{
	if (currentScene != nullptr)
	{
		currentScene->SceneRoot->physicsUpdate(timestep);
		PhysiscsSystem::get()->handleCollisions(currentScene->game_objects);
	}
}

// thanks https://gafferongames.com/post/fix_your_timestep/
void GameSystem::fixedUpdate(float dt)
{
	// Clamp to avoid limit timestep if something goes very wrong...
	const float maxDeltaTime = 0.25f;
	dt = std::min(dt, maxDeltaTime);

	accumulator += dt;

	while (accumulator >= physics_timestep)
	{
		runPhysics(physics_timestep);
		if (currentScene && currentScene->SceneRoot)
		{
			currentScene->SceneRoot->fixedUpdate(physics_timestep);
		}
		accumulator -= physics_timestep;
	}
}


void GameSystem::update(float dt)
{
	if (currentScene != nullptr)
		currentScene->SceneRoot->update(dt);
}

void GameSystem::lateUpdate(float dt)
{
	if (currentScene != nullptr)
		currentScene->SceneRoot->lateUpdate(dt);
}

void GameSystem::render()
{
	window->clear(sf::Color::White);
	if (currentScene != nullptr)
		currentScene->SceneRoot->render(window);
	window->display();
}

void GameSystem::changeScene()
{
	if (scenes[target_scene] != currentScene) {
		// TODO pass persistent objects between scenes.
		if (currentScene != nullptr)
			currentScene->unload();
		currentScene = scenes[target_scene];
		currentScene->load();
	}
}
