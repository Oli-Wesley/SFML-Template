#include "SceneManager.h"
#include "../Singletons/GameInfo.h"

// set to the default scene.
SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	delete states[0];
}

// switches state given on a stateid string.
void SceneManager::switchScene(std::string state_id)
{
	target_state_id = state_id;
}

void SceneManager::switchToTargetScene()
{
	if (current_state == nullptr) {
		for (int i = 0; i < states.size(); i++)
		{
			current_state = states[i];
			current_state->onEnter();
			std::cout << "Switched scene to: `" << current_state->getStateID() << "from: NOSCENE";
			return;
		}
	}

	else if (current_state->getStateID() != target_state_id)
	{
		std::cout << "Attempting to switch scene to: `" << target_state_id << "`"
			<< std::endl;
		SceneInterface* old_scene = current_state;
		for (int i = 0; i < states.size(); i++)
		{
			if (states[i]->getStateID() == target_state_id)
			{
				current_state->onExit();
				current_state = states[i];
				current_state->onEnter();
				std::cout << "Switched scene to: `" << current_state->getStateID()
					<< "` from: `" << old_scene->getStateID() << "`" << std::endl;
				return;
			}
		}
		std::cout << "Failed to switch scene (Given ID is not in array), staying "
			"on :`"
			<< current_state->getStateID() << "`" << std::endl;
		target_state_id = current_state->getStateID();
	}
}

// adds a scene to the sceneManager.
void SceneManager::addScene(SceneInterface* state)
{
	state->initID();
	std::cout << "Added Scene: `" << state->getStateID() << "`: " << state
		<< std::endl;
	states.append(state);
}

void SceneManager::addScene(SceneInterface* state, bool switch_to_scene)
{
	if (switch_to_scene) {
		switchScene(state->getStateID());
	}

	state->initID();
	std::cout << "Added Scene: `" << state->getStateID() << "`: " << state
		<< std::endl;
	states.append(state);
}

void SceneManager::update(float dt)
{
	if (current_state != nullptr)
		current_state->update(dt);
}

void SceneManager::render()
{
	if (current_state != nullptr) 
	{
		GameInfo::getInstance()->window->clear(current_state->getColor());
		current_state->render();
		GameInfo::getInstance()->window->display();
	}
	else {
		GameInfo::getInstance()->window->clear(sf::Color(255, 0, 255));
		GameInfo::getInstance()->window->display();
	}
}

void SceneManager::handleEvent(sf::Event event)
{
	if (current_state != nullptr)
	current_state->handleEvent(event);
}

// outputs the current state
void SceneManager::outputInfo()
{
	if (current_state != nullptr) {
		std::cout << "SceneManagerInfo: \n CurrentState: " << current_state->getStateID() << std::endl;
	}
	else {
		std::cout << "SceneManagerInfo: \n CurrentState: " << "NULLPTR" << std::endl;
	}
}