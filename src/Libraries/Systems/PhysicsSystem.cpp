#include "PhysicsSystem.h"
#include "../Components.h"
#include "../ComponentInterfaces.h"
#include "../GameObject.h"

// Define the static member variable
PhysiscsSystem* PhysiscsSystem::instance = nullptr;

PhysiscsSystem* PhysiscsSystem::get()
{
	if (instance == nullptr)
	{
		instance = new PhysiscsSystem();
	}
	return instance;
}

void PhysiscsSystem::handleCollisions(const std::vector<GameObject*>& gameObjects)
{
	std::vector<CollisionState> currentCollisions;

	for (auto* objA : gameObjects) {
		auto* colA = objA->getComponent<BoxCollider>();
		if (!colA) continue;

		for (auto* objB : gameObjects) {
			if (objA == objB) continue;

			auto* colB = objB->getComponent<BoxCollider>();
			if (!colB) continue;

			if (checkCollision(colA, colB)) {
				bool isTrigger = colA->is_trigger || colB->is_trigger;

				currentCollisions.push_back({ objA, objB, isTrigger });

				// Collision event (and trigger stay)
				for (auto* comp : objA->getAllComponents()) {
					if (auto* script = dynamic_cast<IScriptableBehaviour*>(comp)) {
						if (isTrigger)
							script->onTriggerStay(objB);
						else
							script->onCollision(objB);
					}
				}
				for (auto* comp : objB->getAllComponents()) {
					if (auto* script = dynamic_cast<IScriptableBehaviour*>(comp)) {
						if (isTrigger)
							script->onTriggerStay(objA);
						else
							script->onCollision(objA);
					}
				}

				// Enter trigger
				auto found = std::find(previousFrameCollisions.begin(), previousFrameCollisions.end(),
					CollisionState{ objA, objB, isTrigger });
				if (found == previousFrameCollisions.end()) {
					for (auto* comp : objA->getAllComponents()) {
						if (auto* script = dynamic_cast<IScriptableBehaviour*>(comp)) {
							if (isTrigger) script->onTriggerEnter(objB);
						}
					}
					for (auto* comp : objB->getAllComponents()) {
						if (auto* script = dynamic_cast<IScriptableBehaviour*>(comp)) {
							if (isTrigger) script->onTriggerEnter(objA);
						}
					}
				}

				// if both are not triggers, resolve the collision.
				if (!isTrigger) {
					resolveCollision(objA, objB, objA->getComponent<RigidBody>(), objB->getComponent<RigidBody>());
				}
			}
		}
	}

	// Trigger Exit
	for (auto& prev : previousFrameCollisions) {
		auto stillColliding = std::find(currentCollisions.begin(), currentCollisions.end(), prev) != currentCollisions.end();
		if (!stillColliding && prev.isTrigger) {
			for (auto* comp : prev.a->getAllComponents()) {
				if (auto* script = dynamic_cast<IScriptableBehaviour*>(comp)) {
					script->onTriggerExit(prev.b);
				}
			}
			for (auto* comp : prev.b->getAllComponents()) {
				if (auto* script = dynamic_cast<IScriptableBehaviour*>(comp)) {
					script->onTriggerExit(prev.a);
				}
			}
		}
	}

	previousFrameCollisions = currentCollisions;
}


bool PhysiscsSystem::checkCollision(BoxCollider* a, BoxCollider* b)
{
	sf::FloatRect a_rect = a->getCollider();
	sf::FloatRect b_rect = b->getCollider();

	return (
		a_rect.left < b_rect.left + b_rect.width &&
		a_rect.left + a_rect.width > b_rect.left &&
		a_rect.top < b_rect.top + b_rect.height &&
		a_rect.top + a_rect.height > b_rect.top);
}


// thank you https://www.youtube.com/watch?v=vQO_hPOE-1Y,
// https://gamedev.stackexchange.com/questions/32545/what-is-the-mtv-minimum-translation-vector-in-sat-seperation-of-axis 
// and chatgpt... I was so confused :c
// i kinda half understand how this works....
void PhysiscsSystem::resolveCollision(GameObject* a, GameObject* b, RigidBody* rbA, RigidBody* rbB)
{
	auto colA = a->getComponent<BoxCollider>();
	auto colB = b->getComponent<BoxCollider>();
	if (!colA || !colB) return;

	sf::FloatRect rectA = colA->getCollider();
	sf::FloatRect rectB = colB->getCollider();

	// find amount and direction of overlap
	float deltaX = (rectA.left + rectA.width / 2) - (rectB.left + rectB.width / 2);
	float deltaY = (rectA.top + rectA.height / 2) - (rectB.top + rectB.height / 2);

	float combinedHalfWidths = (rectA.width + rectB.width) / 2;
	float combinedHalfHeights = (rectA.height + rectB.height) / 2;

	float overlapX = combinedHalfWidths - std::abs(deltaX);
	float overlapY = combinedHalfHeights - std::abs(deltaY);

	// check which way to move away (if both are not static 50/50 each way, if 1 not that moves the whole distance, if both static return) 
	bool resolveA = rbA && !rbA->is_static;
	bool resolveB = rbB && !rbB->is_static;

	if (!resolveA && !resolveB) return;

	// Determine collision normal and MTV direction
	sf::Vector2f normal;	
	sf::Vector2f mtv; 

	if (overlapX < overlapY) {
		normal = (deltaX > 0) ? sf::Vector2f(1, 0) : sf::Vector2f(-1, 0);
		mtv = normal * overlapX;
	}
	else {
		normal = (deltaY > 0) ? sf::Vector2f(0, 1) : sf::Vector2f(0, -1);
		mtv = normal * overlapY;
	}

	// Separate the objects
	if (resolveA && resolveB) {
		a->getTransform()->move(mtv.x / 2, mtv.y / 2);
		b->getTransform()->move(-mtv.x / 2, -mtv.y / 2);
	}
	else if (resolveA) {
		a->getTransform()->move(mtv.x, mtv.y);
	}
	else if (resolveB) {
		b->getTransform()->move(-mtv.x, -mtv.y);
	}

	// collision response

	sf::Vector2f velA = rbA ? *rbA->getVelocity() : sf::Vector2f(0, 0);
	sf::Vector2f velB = rbB ? *rbB->getVelocity() : sf::Vector2f(0, 0);

	sf::Vector2f relativeVel = velA - velB;
	float velAlongNormal = relativeVel.x * normal.x + relativeVel.y * normal.y;

	if (velAlongNormal > 0) return; // moving apart

	// calculate bounce.
	float restitution = std::min(
		rbA ? rbA->bouncyness : 0.0f,
		rbB ? rbB->bouncyness : 0.0f
	);


	float invMassA = (rbA && !rbA->is_static) ? 1.0f / rbA->mass : 0.0f;
	float invMassB = (rbB && !rbB->is_static) ? 1.0f / rbB->mass : 0.0f;
	float totalInvMass = invMassA + invMassB;

	if (totalInvMass == 0.0f) return;

	// Normal impulse
	float j = -(1.0f + restitution) * velAlongNormal;
	j /= totalInvMass;

	sf::Vector2f impulse = j * normal;

	if (rbA && !rbA->is_static)
		*rbA->getVelocity() += impulse * invMassA;

	if (rbB && !rbB->is_static)
		*rbB->getVelocity() -= impulse * invMassB;

	// friction.

	relativeVel = velA - velB;
	sf::Vector2f tangent = relativeVel - (dot(relativeVel, normal) * normal);
	if (tangent.x != 0 || tangent.y != 0)
		tangent /= std::sqrt(tangent.x * tangent.x + tangent.y * tangent.y); // normalize

	float friction = std::min(
		rbA ? rbA->friction : 0.0f,
		rbB ? rbB->friction : 0.0f
	);

	float jt = -dot(relativeVel, tangent);
	jt /= totalInvMass;

	sf::Vector2f frictionImpulse = jt * friction * tangent;

	if (rbA && !rbA->is_static)
		*rbA->getVelocity() += frictionImpulse * invMassA;

	if (rbB && !rbB->is_static)
		*rbB->getVelocity() -= frictionImpulse * invMassB;
}

float PhysiscsSystem::dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}
