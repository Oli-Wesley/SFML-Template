#include "SpriteGameObject.h"
#include "../Singletons/GameInfo.h"
#include <iostream>


SpriteGameObject::SpriteGameObject()
{

}

SpriteGameObject::~SpriteGameObject()
{
    for (int i = 0; i < textures.size(); i++) {
      delete textures[i]; 
        textures.pop(i);
    }
    delete sprite;
}

sf::FloatRect SpriteGameObject::getRect() {
  updateSprite();
  sf::FloatRect bounds = sprite->getGlobalBounds();
  return bounds;
}

void SpriteGameObject::setFrame(int _frame) {
  target_texture_frame = _frame;
}

int SpriteGameObject::getFrame() {
  return target_texture_frame;
}

bool SpriteGameObject::addFrame(std::string _path) 
{
  sf::Texture* temp_tex = new sf::Texture();
  if (temp_tex->loadFromFile(_path))
  {
    textures.append(temp_tex);
    if (textures.size() == 1)
    {
      sprite->setTexture(*textures[0], true);
      cur_texture_frame = 0;
    }
    return true;
  }
  std::cout << "failed to load image from: " << _path << std::endl;
  return false;
}

void SpriteGameObject::render()
{
  if (is_drawn)
  {
    updateSprite();

    // draw to window
    GameInfo::getInstance()->window->draw(*sprite);
  }
}

void SpriteGameObject::updateSprite() 
{
  // set texture frame.
  if (cur_texture_frame != target_texture_frame)
  {
    sprite->setTexture(*textures[target_texture_frame], true);
    cur_texture_frame = target_texture_frame;
  }
  // set sprite colour
  if (sprite->getColor() != colour)
  {
    sprite->setColor(colour);
  }

  // apply position, scale, colour ect(this seems pretty inexpensive so I
  // think no need for if statements)
  sprite->setPosition(position->x + offset->x, position->y + offset->y);
  sprite->setScale(scale->x, scale->y);
}

