#include "WanderBehavior.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <ctime>

WanderBehavior::WanderBehavior() : rng(std::time(nullptr)) {
  wanderTarget = sf::Vector2f(wanderRadius, 0);
}

sf::Vector2f WanderBehavior::calculateMovement(const sf::Vector2f &currentPos,
                                               const sf::Vector2f &currentVel,
                                               float deltaTime) {
  // 1. Add a small random vector to the target's position
  wanderTarget += getRandomVector() * wanderJitter * deltaTime;

  // 2. Reproject this new target onto the wander circle
  wanderTarget = normalize(wanderTarget) * wanderRadius;

  // 3. Move the target into a position wanderDistance units in front of the
  // agent
  sf::Vector2f currentDirection = normalize(currentVel);
  sf::Vector2f circleCenter = currentDirection * wanderDistance;

  // 4. The final target is the circle's center plus the offset
  sf::Vector2f target = circleCenter + wanderTarget;

  // 5. Return the steering force towards the target
  return normalize(target) * 100.0f; // Scale force as needed
}

sf::Vector2f WanderBehavior::getRandomVector() {
  // Generate random direction vector
  std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
  return sf::Vector2f(dist(rng), dist(rng));
}

sf::Vector2f WanderBehavior::normalize(const sf::Vector2f &v) {
  float length = std::sqrt(v.x * v.x + v.y * v.y);
  if (length != 0) {
    return v / length;
  }
  return v;
}
