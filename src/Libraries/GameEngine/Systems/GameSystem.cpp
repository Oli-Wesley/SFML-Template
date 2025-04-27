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
	switchScene(start_scene); // change target scene.
	changeScene(); // actually change into the scene.
	start(); // call the other start function that contains the gameLoop.
}

void GameSystem::addScene(Scene* scene, std::string scene_name)
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
		currentScene->scene_root->physicsUpdate(timestep);
		PhysiscsSystem::get()->handleCollisions(currentScene->scene_root->getAllChilderenWithComponent<BoxCollider>());
	}
}

// thanks https://gafferongames.com/post/fix_your_timestep/
void GameSystem::fixedUpdate(float dt)
{
	// Clamp to limit timestep if something goes very wrong...
	const float maxDeltaTime = 0.25f;
	dt = std::min(dt, maxDeltaTime);

	accumulator += dt;

	// this allows for multiple physics ticks to be ran in a single frame, or none at all if it's not needed.
	while (accumulator >= physics_timestep)
	{
		runPhysics(physics_timestep);
		std::vector<GameObject*> test;
		if (currentScene && currentScene->scene_root)
		{
			currentScene->scene_root->fixedUpdate(physics_timestep);
		}
		accumulator -= physics_timestep;
	}
}


void GameSystem::update(float dt)
{
	if (currentScene != nullptr)
		currentScene->scene_root->update(dt);
}

void GameSystem::lateUpdate(float dt)
{
	if (currentScene != nullptr)
		currentScene->scene_root->lateUpdate(dt);
}

void GameSystem::render()
{
	window->clear(sf::Color::White);
	if (currentScene != nullptr) {
		std::vector<IRenderable*> renderables = currentScene->scene_root->render();
		// simple bubble sort implimentation, sort the list based on layer.
		bool changed = 1;
		IRenderable* hold;
		int length = renderables.size();

		while (changed)
		{
			changed = 0;
			for (int index = 0; index < length - 1; index++)
			{
				if (renderables[index]->getRenderOrder() > renderables[index + 1]->getRenderOrder())
				{
					hold = renderables[index];
					renderables[index] = renderables[index + 1];
					renderables[index + 1] = hold;
					changed = 1;
				}
			}
		}
		for (IRenderable* var : renderables)
		{
			var->render(window);
		}
	}
	window->display();
}

void GameSystem::changeScene()
{
	if (scenes[target_scene] != currentScene) {
		// TODO pass persistent objects between scenes.
		GameObject* dont_destroy = nullptr;
		if (currentScene != nullptr)
			dont_destroy = currentScene->unload();
		currentScene = scenes[target_scene];
		currentScene->load(dont_destroy);
	}
}
