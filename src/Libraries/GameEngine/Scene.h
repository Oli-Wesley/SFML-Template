#pragma once

#include <vector>
// prototype gameObject so it is happy at compile time.
class GameObject;

class Scene {
public:
	Scene();
	~Scene();
	GameObject* scene_root; // Empty GameObject at 0,0 where everything starts from.
	GameObject* dont_destroy;

	GameObject* unload(); // Returns Game Objects with Persistance between scenes (and their childeren)
	
	virtual void load(GameObject* dont_destroy);

protected:
	virtual void load() = 0; // Every scene needs a load function.
	virtual void onUnload() {};
};