#include <SFML/Graphics.hpp>
#include "Libraries/GameObject.h"
#include "Libraries/Components/Transform.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Component System");
    window.setFramerateLimit(60);

    sf::Clock clock;

    GameObject* test = new GameObject();
    GameObject* test2 = new GameObject();

    test->GetComponent<Transform>().setLocalPosition(100, 100);
    test->AddChild(test2);
    test2->GetComponent<Transform>().setLocalPosition(20, 20);
    std::cout << test2->GetComponent<Transform>().getGlobalPosition().x << ", ";
    std::cout << test2->GetComponent<Transform>().getGlobalPosition().y << std::endl;
    test2->GetComponent<Transform>().setLocalPosition(-150, -150);
    std::cout << test2->GetComponent<Transform>().getGlobalPosition().x << ", ";
    std::cout << test2->GetComponent<Transform>().getGlobalPosition().y << std::endl;
    test2->GetComponent<Transform>().setGlobalPosition(50, 50);
    std::cout << test2->GetComponent<Transform>().getGlobalPosition().x << ", ";
    std::cout << test2->GetComponent<Transform>().getGlobalPosition().y << std::endl;


    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
        }
        float dt = clock.restart().asSeconds();
        window.clear();
        window.display();
    }
    return 0;
}
