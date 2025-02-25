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
      if (game_objects[i]->checkOnScreen())
        game_objects[i]->render();
    }
  }

  void checkDestroyed()
  {
    for (int i = 0; i < game_objects.size(); i++)
    {
      if (game_objects[i]->isDestroyed())
      {
        delete game_objects[i];
        game_objects.pop(i);
      }
    }
  }

  void checkCollisions()
  {
    for (int i = 0; i < game_objects.size(); i++)
    {
      for (int ii = 0; ii < game_objects.size(); ii++)
      {
        if (i != ii)
        {
          GameObject::CollisionInfo colinfo =
            game_objects[i]->checkCollision(game_objects[ii]);
          if (colinfo != GameObject::NoCollision)
            game_objects[i]->onCollision(game_objects[ii], colinfo);
        }
      }
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

  void addGameObject(GameObject* new_obj) { game_objects.append(new_obj); };

  virtual void init()                       = 0;
  virtual void update(float dt)             = 0;
  virtual void handleEvent(sf::Event event) = 0;
  virtual void onEnter()                    = 0;
  virtual void onExit()                     = 0;
  virtual void initID()                     = 0;
  virtual void receiveMessage(std::string _message)
  {
    std::cout << getStateID() << "scene has received a message (" << _message
              << ") but does not have a way to "
                 "handle it setup.\n";
  };
  virtual void receiveMessage(std::string _message, int _value)
  {
    std::cout << getStateID() << "scene has received a message (" << _message
              << ", " << _value
              << ") but does not have a way to "
                 "handle it setup.\n";
  };

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