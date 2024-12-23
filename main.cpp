#include "World.h"
#include <SFML/Graphics.hpp>

int main() {
  const unsigned int windowWidth = 500;
  const unsigned int windowHeight = 500;

  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                          "Ant Simulator");
  window.setFramerateLimit(60);

  World world(windowWidth, windowHeight);

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    float deltaTime = clock.restart().asSeconds();

    world.update(deltaTime);

    window.clear(sf::Color::Black);
    world.draw(window);
    window.display();
  }

  return 0;
}