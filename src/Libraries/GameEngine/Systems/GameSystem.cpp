#include "GameSystem.h"
#include "../Scene.h"
#include "PhysicsSystem.h"
#include <iostream>
#include "AudioSystem.h"

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

void GameSystem::start(std::string start_scene)
{
	std::cout << "PRESS F1 To Show scene_root Tree\n";
	std::cout << "PRESS F2 To Show dont_destroy Tree\n";
	std::cout << "PRESS F3 To Toggle Debug\n";

	switchScene(start_scene); // change target scene.
	changeScene();            // actually change into the scene.

	window = std::make_unique<sf::RenderWindow>(resolution, window_title);
	window->setFramerateLimit(framerate);

	clock.restart();
	while (window->isOpen())
	{
		sf::Event e;
		while (window->pollEvent(e))
		{
			if (e.type == sf::Event::Closed) {
				if (currentScene)
				{
					// unload current scene
					currentScene->unload();
					// destroy dont_destroy to allow anything attatched to it to run its unload functions.
					currentScene->dont_destroy = nullptr;
				}
				// close the window.
				window->close();
				return;
			}
			// debug keys
			else if (e.type == sf::Event::KeyPressed) {
				if (e.key.code == sf::Keyboard::F1)
				{
					if (currentScene != nullptr && currentScene->scene_root)
						currentScene->scene_root->outputChildrenTree();
				}
				else if (e.key.code == sf::Keyboard::F2)
				{
					if (currentScene != nullptr && currentScene->dont_destroy)
						currentScene->dont_destroy->outputChildrenTree();
				}
				else if (e.key.code == sf::Keyboard::F3)
					setDebug(!isDebug());
			}
		}
		runGameLoop(clock.restart().asSeconds()); // pass time since last frame as
		// dt to the current gameLoop.
	}
}

void GameSystem::addScene(Scene* scene, std::string scene_name)
{
	scenes.emplace(scene_name, scene);
}

Scene* GameSystem::getCurrentScene()
{
	return currentScene;
}

void GameSystem::switchScene(std::string scene_name)
{
	if (scenes[scene_name])
		target_scene = scene_name;
	else
		std::cout << "SCENE DOES NOT EXIST, FAILED TO LOAD SCENE. '" << scene_name
		<< "'\n";
}

void GameSystem::removeScene(std::string scene_name)
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
	update(dt); // first update tick
	lateUpdate(dt); // second update tick 
	render(); // render everything to screen
	AudioSystem::setupPlayers(); // play all sounds that have been added this tick.
	changeScene(); // change scene (at the end to allow the tick to finish)
	flushDestroyQueue();
}

void GameSystem::setTitle(std::string _title)
{
	window_title = _title;
	if (window != nullptr)
		window->setTitle(_title);
}

void GameSystem::setResolution(sf::Vector2i res)
{
	resolution = sf::VideoMode(res.x, res.y);
	if (window != nullptr)
		window->setSize(sf::Vector2u(resolution.width, resolution.height));
}

void GameSystem::setResolution(int x, int y)
{
	setResolution(sf::Vector2(x, y));
}

void GameSystem::setFullscreen(bool state)
{
	// TODO THIS:
}

void GameSystem::setFramerate(float _framerate)
{
	framerate = _framerate;
	if (window != nullptr)
		window->setFramerateLimit(framerate);
}

void GameSystem::setPhysicsTimestep(float tickspersecond)
{
	physics_timestep = 1.0f / tickspersecond;
}

bool GameSystem::isDebug()
{
	return is_debug;
}

void GameSystem::setDebug(bool flag)
{
	is_debug = flag;
	std::cout << "Toggled Debug: " << is_debug << "\n";
}

sf::RenderWindow* GameSystem::getWindow()
{
	return window.get();
}

void GameSystem::addToDestroyQueue(GameObject* obj)
{
	destroy_queue.insert(destroy_queue.begin(), obj);
}

void GameSystem::runPhysics(float timestep)
{
	if (currentScene != nullptr)
	{
		currentScene->scene_root->physicsUpdate(timestep);
		PhysiscsSystem::get()->handleCollisions(
			currentScene->scene_root->getAllChilderenWithComponent<BoxCollider>());
	}
}

// thanks https://gafferongames.com/post/fix_your_timestep/
void GameSystem::fixedUpdate(float dt)
{
	// Clamp to limit timestep if something goes very wrong...
	const float maxDeltaTime = 0.25f;
	dt = std::min(dt, maxDeltaTime);

	accumulator += dt;

	// this allows for multiple physics ticks to be ran in a single frame, or none
	// at all if it's not needed.
	while (accumulator >= physics_timestep)
	{
		runPhysics(physics_timestep);
		if (currentScene && currentScene->scene_root && currentScene->dont_destroy)
		{
			currentScene->scene_root->fixedUpdate(physics_timestep);
			currentScene->dont_destroy->fixedUpdate(physics_timestep);
		}
		accumulator -= physics_timestep;
	}
}

void GameSystem::update(float dt)
{
	if (currentScene != nullptr) {
		currentScene->scene_root->update(dt);
		currentScene->dont_destroy->update(dt);
	}

}

void GameSystem::lateUpdate(float dt)
{
	if (currentScene != nullptr)
		currentScene->scene_root->lateUpdate(dt);
}

void GameSystem::render()
{
	if (currentScene != nullptr)
	{
		window->clear(currentScene->getSceneColor());
		// get all renderables from the scene (scene_root and dont_destroy)
		std::vector<IRenderable*> renderables = currentScene->scene_root->render();
		std::vector<IRenderable*> other = currentScene->dont_destroy->render();
		renderables.insert(renderables.end(), other.begin(), other.end());
		// simple bubble sort, sort the list based on layer. (kinda slow but its fast enough for this..)
		bool changed = 1;
		IRenderable* hold;
		int length = renderables.size();
		while (changed)
		{
			changed = 0;
			for (int index = 0; index < length - 1; index++)
			{
				if (
					renderables[index]->getRenderOrder() >
					renderables[index + 1]->getRenderOrder())
				{
					hold = renderables[index];
					renderables[index] = renderables[index + 1];
					renderables[index + 1] = hold;
					changed = 1;
				}
			}
		}
		// render now sorted list
		for (IRenderable* var : renderables)
		{
			var->render(getWindow());
		}
	}
	else
		window->clear(sf::Color::White); // still clear screen to white if the scene is nullptr
	window->display();
}

void GameSystem::changeScene()
{
	// if scene is different
	if (scenes[target_scene] != currentScene)
	{
		std::unique_ptr<GameObject> dont_destroy = nullptr;

		// move dont_destroy between scenes. 
		if (currentScene != nullptr)
			dont_destroy = currentScene->unload();
		// get current scene and load it
		currentScene = scenes[target_scene];
		if (currentScene)
			currentScene->load(std::move(dont_destroy));
		else
			std::cout << "FAILED TO LOAD SCENE, SCENE EXISTS BUT RETURNS NULLPTR";
		// resize to window size.
		currentScene->onWindowResize(sf::Vector2i(resolution.width, resolution.height));
	}
}

void GameSystem::flushDestroyQueue()
{
	for (GameObject* obj : destroy_queue)
	{
		if (!obj) continue;

		// remove object from parent
		if (GameObject* parent = obj->getParent())
		{
			parent->releaseChild(obj); // allow the object to go ot of scope, destroying it 
		}
	}
	// empty destroy queue. 
	destroy_queue.clear();
}
