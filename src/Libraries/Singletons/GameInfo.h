#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "../SceneManager/SceneManager.h"
#include "SFML/Graphics.hpp"

class GameInfo
{
 public:
  // Public accessor for the singleton instance
  static GameInfo* getInstance();

  // GameInfo values
  sf::RenderWindow* window = nullptr;
  SceneManager* Scenes     = nullptr;

 private:
  // Constructor is private to enforce singleton
  GameInfo() = default;

  // Static instance of the singleton
  static GameInfo* instance_;

  // Delete copy constructor and assignment operator
  GameInfo(GameInfo const&)       = delete;
  void operator=(GameInfo const&) = delete;
};

#endif // GameInfo_H