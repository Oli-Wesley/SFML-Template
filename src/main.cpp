#include "Libraries/Libs.h"
#include "Scenes/scenes.h"

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  // create window and give to the gameInfo singleton to hold for other things
  // to use.
  GameInfo::getInstance()->window =
    new sf::RenderWindow(Settings::getInstance()->resolution, "Window");
  if (Settings::getInstance()->framerate != 0)
    GameInfo::getInstance()->window->setFramerateLimit(
      Settings::getInstance()->framerate);

  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  // initialise an instance of the state_manager, then add all scenes. 
  GameInfo::getInstance()->Scenes = new SceneManager;
  //GameInfo::getInstance()->Scenes->addScene(new TitleScene());
  //GameInfo::getInstance()->Scenes->switchScene("Title");

  // Game loop: run the program as long as the window is open
  while (GameInfo::getInstance()->window->isOpen())
  {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;

    // calculate delta time
    sf::Time time = clock.restart();
    float dt      = time.asSeconds();

    // handle inputs
    while (GameInfo::getInstance()->window->pollEvent(event))
    {
      // close window if event is closed.
      if (event.type == sf::Event::Closed)
      {
        GameInfo::getInstance()->window->close();
      }
      else if (event.type == sf::Event::Resized)
      {
        GameInfo::getInstance()->window->setSize(sf::Vector2u(
          Settings::getInstance()->resolution.width,
          Settings::getInstance()->resolution.height));
      }
      // otherwise pass to the current scene to handle.
      GameInfo::getInstance()->Scenes->handleEvent(event);
    }

    // pass to current scene to handle update.
    GameInfo::getInstance()->Scenes->update(dt);

    // call the current scene to render
    GameInfo::getInstance()->Scenes->render();

    // Only Change scene once the scene has finished updating and rendering ect, prevents double switches and nullptrs where onExit has been called during update and before render
    GameInfo::getInstance()->Scenes->switchToTargetScene();
  }
  return 0;
}