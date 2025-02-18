#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H

#include "../DataStructures/DynamicArray.h"
#include "../DataStructures/Vector2.h"
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	enum CollisionInfo
	{
		NoCollision,
		Top,
		Right,
		Bottom,
		Left
	};

	enum PlacementInfo
	{
		C,
		CT,
		CB,
		L,
		LT,
		LB,
		R,
		RT,
		RB
	};
	GameObject();
	~GameObject();

	// setters and getters for all class vars
	Vector2* getVector();
	void setVector(float x, float y);
	void setVector(float x, float y, bool normalise);

	Vector2* getPosition();
	void setPosition(float x, float y);

	Vector2* getScale();
	void setScale(float x, float y);

	sf::Color* getColour();
	void setColour(sf::Color);

	std::string getID();
	void setID(std::string _id);

	void setRendered(bool _val);
	bool isRendered();

	void setActive(bool _val);
	bool isActive();

	void setLayer(int _layer);
	int getLayer();

	void setPosition(float x, float y, PlacementInfo placementinfo);
	bool checkPointIntersection(sf::Vector2i position);
	bool checkBoxIntersection(GameObject* other);
	CollisionInfo checkCollision(GameObject* other);

	// implemented by sub classes.
	virtual sf::FloatRect getRect() = 0;
	virtual void init() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void handleEvent(sf::Event) = 0;

	

protected:
	int layer = 1;
	Vector2* vector = new Vector2(0, 0);
	Vector2* position = new Vector2(0, 0);
	Vector2* scale = new Vector2(1, 1);
	sf::Color colour = sf::Color::White;
	std::string obj_id = "Unknown";
	bool is_active = true;
	bool is_drawn = true;
};

#endif // BREAKOUT_GAMEOBJECT_H
