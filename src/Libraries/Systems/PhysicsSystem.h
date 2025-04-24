#pragma once

#include "../Components/BoxCollider.h"
#include "../Components/RigidBody.h"

class PhysiscsSystem {
protected:
	struct CollisionState {
		GameObject* a;
		GameObject* b;
		bool isTrigger = false;

		bool operator==(const CollisionState& other) const {
			return (a == other.a && b == other.b) || (a == other.b && b == other.a);
		}
	};

public:
	static PhysiscsSystem* get();
	void handleCollisions(const std::vector<GameObject*>& gameObjects);
	std::vector<CollisionState> currentCollisions;
protected:
	std::vector<CollisionState> previousFrameCollisions;
	
	
	bool checkCollision(BoxCollider* a, BoxCollider* b);
	void resolveCollision(GameObject* a, GameObject* b, RigidBody* rbA, RigidBody* rbB);
	float dot(const sf::Vector2f& a, const sf::Vector2f& b);

	static PhysiscsSystem* instance;
	PhysiscsSystem() = default;
	PhysiscsSystem(PhysiscsSystem const&) = delete;
	void operator=(PhysiscsSystem const&) = delete;
};