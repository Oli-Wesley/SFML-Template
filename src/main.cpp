#include <SFML/Graphics.hpp>
#include "Libraries/GameObject.h"
#include "Libraries/Components.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Component System");
	window.setFramerateLimit(60);

	sf::Clock clock;

	GameObject* test = new GameObject();
	test->addComponent<SpriteRenderer>();
	test->addComponent<BoxCollider>(true);

	GameObject* test2 = new GameObject();

	test2->addComponent<BoxCollider>(true);
	test2->getTransform()->setLocalPosition(5, 5);
	test->addChild(test2);



	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
		}
		float dt = clock.restart().asSeconds();

		// update
		test->getTransform()->move(1, 1);
		test->getTransform()->modifyScale(0.1, 0.1);
		test2->getTransform()->modifyScale(0, 0);

		// render
		window.clear(sf::Color::White);
		test->render(window);
		window.display();
	}
	return 0;
}
