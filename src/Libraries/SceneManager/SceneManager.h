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
  void addScene(SceneInterface* state, bool switch_to_scene = false);


  // passed to the current scene
  void update(float dt);
  void render();
  void handleEvent(sf::Event);
  void outputInfo();

 private:
  // pointer to current state.
  SceneInterface* current_state = nullptr;
  std::string target_state_id   = "";

  // pointers to state instances.

  DynamicArray<SceneInterface*> states;
};

#endif // !STATE_MANAGER_H
