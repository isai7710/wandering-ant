#include "World.h"
#include "SeekBehavior.h"
#include "WanderBehavior.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <memory>

World::World(unsigned int width, unsigned int height)
    : width(width), height(height) {
  ants.reserve(NUM_ANTS);
  setupAnts();
}

void World::update(float deltaTime) {
  for (auto &ant : ants) {
    ant.update(deltaTime);
  }
  if (hasTarget) {
    for (auto &ant : ants) {
      sf::Vector2f error = targetPosition - ant.getPosition();
      if (std::sqrt(error.x * error.x + error.y * error.y) < 2.0f) {
        clearTarget();
      }
    }
  }
}

void World::draw(sf::RenderWindow &window) {
  for (const auto &ant : ants) {
    window.draw(ant);
  }
  if (hasTarget) {
    window.draw(target);
  }
}

void World::updateTarget(sf::Vector2f position) {
  if (targetPosition == position) {
    clearTarget();
    return;
  } else {
    targetPosition = position;
    target.setPosition(targetPosition.x - target.getRadius(),
                       targetPosition.y - target.getRadius());
    target.setFillColor(sf::Color::Green);
    hasTarget = true;
  }
  for (auto &ant : ants) {
    auto seekBehavior = std::make_unique<SeekBehavior>(targetPosition);
    ant.setBehavior(std::move(seekBehavior));
  }
}

sf::Vector2f World::getTargetPosition() { return targetPosition; }

void World::setupAnts() {
  for (std::size_t i = 0; i < NUM_ANTS; i++) {
    Ant ant(width, height);
    ant.setPosition(sf::Vector2f(width / 2.f, height / 2.f));
    auto wanderBehavior = std::make_unique<WanderBehavior>();
    ant.setBehavior(std::move(wanderBehavior));
    ants.push_back(std::move(ant));
  }
}

void World::clearTarget() {
  hasTarget = false;
  targetPosition = {0.0f, 0.0f};
  target.setFillColor(sf::Color::Transparent);
  for (auto &ant : ants) {
    auto wanderBehavior = std::make_unique<WanderBehavior>();
    ant.setBehavior(std::move(wanderBehavior));
  }
}
