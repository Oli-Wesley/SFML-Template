#include "GameObject.h"
#include "../Singletons/GameInfo.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	delete vector;
	delete position;
	delete scale;
    delete offset;
}

Vector2* GameObject::getVector()
{
	return vector;
}

void GameObject::setVector(float x, float y)
{
	vector->x = x;
	vector->y = y;
}

void GameObject::setVector(float x, float y, bool normalise)
{
	vector->x = x;
	vector->y = y;
	if (normalise)
	{
		vector->normalise();
	}
}

Vector2* GameObject::getPosition()
{
	return position;
}

void GameObject::setPosition(float x, float y)
{
	position->x = x;
	position->y = y;
}

Vector2* GameObject::getScale()
{
	return scale;
}

void GameObject::setScale(float x, float y)
{
	scale->x = x;
	scale->y = y;
}

sf::Color* GameObject::getColour()
{
	return &colour;
}

void GameObject::setColour(sf::Color _col)
{
	colour = _col;
}

std::string GameObject::getID()
{
	return obj_id;
}

void GameObject::setID(std::string _ID)
{
	obj_id = _ID;
}

void GameObject::setRendered(bool _val)
{
	is_drawn = _val;
}

bool GameObject::isRendered()
{
	return is_drawn;
}

void GameObject::setActive(bool _val)
{
	is_active = _val;
}

bool GameObject::isActive()
{
	return is_active;
}

void GameObject::destroy() 
{
  if (!is_destroy)
    onDestroy();
  is_destroy = true; 
  
}

bool GameObject::isDestroyed()
{
  return is_destroy;
}

void GameObject::setLayer(int _layer)
{
	layer = _layer;
}

int GameObject::getLayer()
{
	return layer;
}

void GameObject::setPosition(float x, float y, PlacementInfo placementinfo)
{
	sf::FloatRect bounds = getRect();
	Vector2 newPosition(x, y);

	switch (placementinfo)
	{
	case C:
		newPosition.x -= bounds.width / 2;
		newPosition.y -= bounds.height / 2;
		break;
	case CT:
		newPosition.x -= bounds.width / 2;
		break;
	case CB:
		newPosition.x -= bounds.width / 2;
		newPosition.y -= bounds.height;
		break;
	case L:
		newPosition.y -= bounds.height / 2;
		break;
	case LT:
		break; // No adjustment needed
	case LB:
		newPosition.y -= bounds.height;
		break;
	case R:
		newPosition.x -= bounds.width;
		newPosition.y -= bounds.height / 2;
		break;
	case RT:
		newPosition.x -= bounds.width;
		break;
	case RB:
		newPosition.x -= bounds.width;
		newPosition.y -= bounds.height;
		break;
	}
	position->x = newPosition.x;
	position->y = newPosition.y;
}

bool GameObject::checkPointIntersection(sf::Vector2i _position)
{
  if (is_collidable)
  {
    sf::FloatRect bounds = getRect();

    // Check if the point is inside the bounds
    return (
      bounds.left <= _position.x && _position.x <= bounds.left + bounds.width &&
      bounds.top <= _position.y && _position.y <= bounds.top + bounds.height);
  }
}

bool GameObject::checkBoxIntersection(GameObject* other)
{
  if (is_collidable)
  {
	// apply position, scale so bounds are most up to date.
	sf::FloatRect bounds = getRect();
	sf::FloatRect other_rect = other->getRect();
	
	return (
		bounds.left < other_rect.left + other_rect.width &&
		bounds.left + bounds.width > other_rect.left &&
		bounds.top < other_rect.top + other_rect.height &&
		bounds.top + bounds.height > other_rect.top);
  }
}

bool GameObject::checkOnScreen()
{
  sf::FloatRect bounds = getRect();
  sf::Vector2u screen = GameInfo::getInstance()->window->getSize();

return !(
    bounds.left + bounds.width < 0 || 
    bounds.left > screen.x ||         
    bounds.top + bounds.height < 0 || 
    bounds.top > screen.y             
  );
}

GameObject::CollisionInfo GameObject::checkCollision(GameObject* other)
{
  if (is_collidable)
  {
    sf::FloatRect this_rect  = getRect();
    sf::FloatRect other_rect = other->getRect();

    // check if it intersects with the other rect, can skip over checking side
    // if it doesn't.
    if (checkBoxIntersection(other))
    {
      // get smallest overlap to find side.
      float top_overlap = (this_rect.top + this_rect.height) - other_rect.top;
      float bottom_overlap =
        (other_rect.top + other_rect.height) - this_rect.top;
      float left_overlap = (this_rect.left + this_rect.width) - other_rect.left;
      float right_overlap =
        (other_rect.left + other_rect.width) - this_rect.left;

      float smallest_overlap =
        std::min({ top_overlap, bottom_overlap, left_overlap, right_overlap });

      if (smallest_overlap == top_overlap)
        return GameObject::CollisionInfo::Top;
      else if (smallest_overlap == right_overlap)
        return GameObject::CollisionInfo::Right;
      else if (smallest_overlap == bottom_overlap)
        return GameObject::CollisionInfo::Bottom;
      else if (smallest_overlap == left_overlap)
        return GameObject::CollisionInfo::Left;
    }
    return GameObject::CollisionInfo::NoCollision;
  }
}
