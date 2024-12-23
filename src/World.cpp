#include "World.h"
#include <SFML/Graphics/Font.hpp>

World::World(unsigned int width, unsigned int height)
    : width(width), height(height) {
  setupAnts();
}

void World::update(float deltaTime) {
  for (auto &ant : ants) {
    ant.update(deltaTime);
  }
}

void World::draw(sf::RenderWindow &window) {
  for (const auto &ant : ants) {
    window.draw(ant);
  }
}

void World::setupAnts() {
  for (int i = 0; i < numAnts; i++) {
    Ant ant(width, height);
    ant.setPosition(sf::Vector2f(width / 2.f, height / 2.f));
    ants.push_back(ant);
  }
}
