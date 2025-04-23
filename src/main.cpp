#include <SFML/Graphics.hpp>
#include "Libraries/GameObject.h"
#include "Libraries/Components.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Component System");
	window.setFramerateLimit(60);

	sf::Clock clock;

	GameObject* test = new GameObject();
	test->addComponent<SpriteRenderer>();
	test->addComponent<Texture>("../Data/Images/ball.png");
	test->addComponent<BoxCollider>(true);
	test->getComponent<BoxCollider>()->setSize(7, 7);
	test->addComponent<RigidBody>();
	test->getTransform()->setLocalScale(50, 50);

	// GameObject* test2 = new GameObject();

	// test2->addComponent<BoxCollider>(true);
	// test2->getTransform()->setLocalPosition(5, 5);
	// test->addChild(test2);

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
		}
		float dt = clock.restart().asSeconds();

		// update
		test->physicsUpdate(dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			test->getComponent<RigidBody>()->applyForce(0, -2);
		// test->getTransform()->move(1, 1);

		// render
		window.clear(sf::Color::White);
		test->render(window);
		
		window.display();
	}
	return 0;
}