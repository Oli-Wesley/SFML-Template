#pragma once
#include <SFML/Graphics.hpp>

// prototype gameObject so it is happy at compile time.
class GameObject;

class IComponent {
public:
	virtual ~IComponent() {};

	// Lifecycle hooks (similar to Unity's MonoBehaviour)
	virtual void Awake() {}      // Called once when the component is initialized
	virtual void Start() {}      // Called once when the GameObject is enabled
	virtual void Sleep() {}      // Called once when the GameObject is disabled
	virtual void Update(float dt) {}     // Called every frame
	virtual void render(sf::View* _view) {}; // Called when the component is rendered
	virtual void OnDestroy() {}  // Called when the component is destroyed	
	void setAttatchedTo(GameObject* gameObject);
protected:
	GameObject* attached_to = nullptr;
};

