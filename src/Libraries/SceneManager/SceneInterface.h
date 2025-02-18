#ifndef SceneInterface_H
#define SceneInterface_H

#include "../DataStructures/DynamicArray.h"
#include "../GameObjects/GameObject.h"
#include "SFML/Graphics.hpp"

// interface for accessing the scene objects
class SceneInterface
{
 public:
  std::string getStateID() { return stateID; };
  void render()
  {
    // sort based on layer.
    sortGameObjects();
    for (int i = 0; i < game_objects.size(); i++)
    {
      game_objects[i]->render();
    }
  }

  sf::Color getColor() { return background_color; };
  void setColor(sf::Color _colour) { background_color = _colour; };

  GameObject* findGameObject(std::string obj_id)
  {
    for (int i = 0; i < game_objects.size(); i++)
    {
      if (game_objects[i]->getID() == obj_id)
        return game_objects[i];
    }
    return nullptr;
  }

  virtual void init()                       = 0;
  virtual void update(float dt)             = 0;
  virtual void handleEvent(sf::Event event) = 0;
  virtual void onEnter()                    = 0;
  virtual void onExit()                     = 0;
  virtual void initID()                     = 0;

 protected:
  std::string stateID = "Unknown"; // Default stateID value
  DynamicArray<GameObject*> game_objects;
  sf::Color background_color = sf::Color::White;

 private:
  void sortGameObjects()
  {
    // simple bubble sort implimentation, sort the list based on layer.
    bool changed = 1;

    GameObject* hold;
    while (changed)
    {
      changed = 0;
      for (int index = 0; index < game_objects.size() - 1; index++)
      {
        if (game_objects[index]->getLayer() > game_objects[index + 1]->getLayer())
        {
          hold                    = game_objects[index];
          game_objects[index]     = game_objects[index + 1];
          game_objects[index + 1] = hold;
          changed                 = 1;
        }
      }
    }
  }
};

#endif // !SceneInterface_H