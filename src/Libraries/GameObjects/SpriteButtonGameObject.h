#ifndef SPRITEBUTTONGAMEOBJECT_H
#define SPRITEBUTTONGAMEOBJECT_H

#include "SpriteGameObject.h"

class SpriteButtonGameObject : public SpriteGameObject
{
 public:
  void handleEvent(sf::Event);
  void setDefaultIndex(int frame_index);
  void setHoverIndex(int frame_index);
  void setClickIndex(int frame_index);

  virtual void update(float dt) = 0;
  virtual void init()           = 0;
  virtual void onHover() = 0;
  virtual void onClick() = 0;

 protected:
  bool is_hovered  = false;
  bool is_clicked  = false;
  bool is_disabled = false;

  int default_sprite_index = 0;
  int hover_sprite_index = 1;
  int click_sprite_index = 1;
};
#endif // !SPRITEBUTTONGAMEOBJECT_H