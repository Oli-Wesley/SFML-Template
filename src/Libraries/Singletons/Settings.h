#ifndef SETTINGS_H
#define SETTINGS_H

#include "SFML/Graphics.hpp"

class Settings
{
 public:
  // Public accessor for the singleton instance
  static Settings* getInstance();

  // settings values
  sf::VideoMode resolution = sf::VideoMode(1080, 720);
  bool allow_resize        = false;
  int framerate            = 0; // 0 is unlimited.

  float master_volume = 0.5f;
  float sfx_volume    = 0.5f;
  float music_volume  = 0.5f;

  // game specific settings
  sf::Keyboard::Key up_key    = sf::Keyboard::Key::W;
  sf::Keyboard::Key down_key  = sf::Keyboard::Key::S;
  sf::Keyboard::Key left_key  = sf::Keyboard::Key::A;
  sf::Keyboard::Key right_key = sf::Keyboard::Key::D;
  sf::Keyboard::Key pause_key = sf::Keyboard::Key::Escape;

 private:
  // Constructor is private to enforce singleton
  Settings() = default;

  // Static instance of the singleton
  static Settings* instance_;

  // Delete copy constructor and assignment operator
  Settings(Settings const&)       = delete;
  void operator=(Settings const&) = delete;
};

#endif // SETTINGS_H