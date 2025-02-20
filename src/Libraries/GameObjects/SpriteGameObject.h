#ifndef SPRITE_GAME_OBJECT_H
#define SPRITE_GAME_OBJECT_H

#include "GameObject.h"

class SpriteGameObject : public GameObject
{
 public:
  SpriteGameObject();
  virtual ~SpriteGameObject();

  virtual void update(float dt)       = 0;
  virtual void handleEvent(sf::Event) = 0;
  virtual void init()                 = 0;

  sf::FloatRect getRect();

  void setFrame(int frame);
  int getFrame();
  int getFrameCount() { return textures.size(); };
  bool addFrame(std::string _path);
  DynamicArray<sf::Texture*>* getFrames() { return &textures; };

  void render();

 protected:
  sf::Sprite* sprite = new sf::Sprite;
  DynamicArray<sf::Texture*> textures;
  int cur_texture_frame    = -1;
  int target_texture_frame = 0;
};

#endif
