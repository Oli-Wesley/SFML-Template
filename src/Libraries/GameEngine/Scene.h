#pragma once

#include <vector>
// prototype gameObject so it is happy at compile time.
class GameObject;

class Scene {
public:
	GameObject* SceneRoot; // Empty GameObject at 0,0 where everything starts from.

	void unload(); // Returns Game Objects with Persistance between scenes (and their childeren)
	virtual void load() = 0; // Every scene needs a load function.
};