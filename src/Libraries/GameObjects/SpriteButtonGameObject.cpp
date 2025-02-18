#include "SpriteButtonGameObject.h"
#include "../Singletons/GameInfo.h"

void SpriteButtonGameObject::handleEvent(sf::Event _event)
{
  if (_event.type == sf::Event::MouseMoved)
  {
    if (checkPointIntersection(
          sf::Mouse::getPosition(*GameInfo::getInstance()->window)))
    {
      is_hovered           = true;
      target_texture_frame = hover_sprite_index;
      onHover();
    }
    else
    {
      is_hovered           = false;
      target_texture_frame = default_sprite_index;
    }
  }
  else if (_event.type == sf::Event::MouseButtonPressed && is_hovered)
  {
    if (_event.mouseButton.button == sf::Mouse::Button::Left)
    {
      is_clicked           = true;
      target_texture_frame = click_sprite_index;
      onClick();
    }
  }
  else if (_event.type == sf::Event::MouseButtonReleased && is_hovered)
  {
    if (_event.mouseButton.button == sf::Mouse::Left)
    {
      is_clicked           = false;
      target_texture_frame = hover_sprite_index;
    }
  }
}

void SpriteButtonGameObject::setDefaultIndex(int frame_index)
{
  default_sprite_index = frame_index;
}

void SpriteButtonGameObject::setHoverIndex(int frame_index)
{
  hover_sprite_index = frame_index;
}

void SpriteButtonGameObject::setClickIndex(int frame_index)
{
  click_sprite_index = frame_index;
}