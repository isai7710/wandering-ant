#include "World.h"
#include <SFML/Graphics/Font.hpp>

World::World(unsigned int width, unsigned int height)
    : width(width), height(height) {
  ants.reserve(NUM_ANTS);
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
  for (int i = 0; i < NUM_ANTS; i++) {
    Ant ant(width, height);
    ant.setPosition(sf::Vector2f(width / 2.f, height / 2.f));
    ant.setVelocity(sf::Vector2f(40.0f, 40.0f));
    ants.push_back(std::move(ant));
  }
}
