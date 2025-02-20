#include "SceneManager.h"
#include "../Singletons/GameInfo.h"

// set to the default scene.
SceneManager::SceneManager() {}

SceneManager::~SceneManager()
{
  delete scenes[0];
}

// switches state given on a stateid string.
void SceneManager::switchScene(std::string state_id)
{
  target_scene_id = state_id;
}

void SceneManager::switchToTargetScene()
{
  if (current_scene == nullptr)
  {
    for (int i = 0; i < scenes.size(); i++)
    {
      current_scene = scenes[i];
      current_scene->onEnter();
      std::cout << "Switched scene to: `" << current_scene->getStateID()
                << "` from: NOSCENE \n";
      return;
    }
  }

  else if (current_scene->getStateID() != target_scene_id)
  {
    std::cout << "Attempting to switch scene to: `" << target_scene_id << "`"
              << std::endl;
    SceneInterface* old_scene = current_scene;
    for (int i = 0; i < scenes.size(); i++)
    {
      if (scenes[i]->getStateID() == target_scene_id)
      {
        current_scene->onExit();
        current_scene = scenes[i];
        current_scene->onEnter();
        std::cout << "Switched scene to: `" << current_scene->getStateID()
                  << "` from: `" << old_scene->getStateID() << "`" << std::endl;
        return;
      }
    }
    std::cout << "Failed to switch scene (Given ID is not in array), staying "
                 "on :`"
              << current_scene->getStateID() << "`" << std::endl;
    target_scene_id = current_scene->getStateID();
  }
}

// adds a scene to the sceneManager.
void SceneManager::addScene(SceneInterface* state)
{
  state->initID();
  std::cout << "Added Scene: `" << state->getStateID() << "`: " << state
            << std::endl;
  scenes.append(state);
}

void SceneManager::update(float dt)
{
  if (current_scene != nullptr)
  {
    current_scene->checkCollisions();
    current_scene->update(dt);
    current_scene->checkDestroyed();
  }
}

void SceneManager::render()
{
  if (current_scene != nullptr)
  {
    GameInfo::getInstance()->window->clear(current_scene->getColor());
    current_scene->render();
    GameInfo::getInstance()->window->display();
  }
  else
  {
    GameInfo::getInstance()->window->clear(sf::Color(255, 0, 255));
    GameInfo::getInstance()->window->display();
  }
}

void SceneManager::handleEvent(sf::Event event)
{
  if (current_scene != nullptr)
    current_scene->handleEvent(event);
}

// outputs the current state
void SceneManager::outputInfo()
{
  if (current_scene != nullptr)
  {
    std::cout << "SceneManagerInfo: \n CurrentState: "
              << current_scene->getStateID() << std::endl;
  }
  else
  {
    std::cout << "SceneManagerInfo: \n CurrentState: " << "NULLPTR"
              << std::endl;
  }
}