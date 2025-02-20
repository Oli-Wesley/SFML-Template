#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "../DataStructures/DynamicArray.h"
#include "SFML/Graphics.hpp"
#include "SceneInterface.h"


class SceneManager
{
 public:
  SceneManager();
  ~SceneManager();

  // scene methods. 
  void switchScene(std::string state_id);
  void switchToTargetScene();
  void addScene(SceneInterface* state);


  // passed to the current scene
  void update(float dt);
  void render();
  void handleEvent(sf::Event);
  void outputInfo();

  SceneInterface* getCurrentScene() { return current_scene; };

 private:
  // pointer to current state.
  SceneInterface* current_scene = nullptr;
  std::string target_scene_id   = "";

  // pointers to state instances.

  DynamicArray<SceneInterface*> scenes;
};

#endif // !STATE_MANAGER_H
