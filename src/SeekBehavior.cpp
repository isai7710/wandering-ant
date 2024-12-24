#include "SeekBehavior.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>

SeekBehavior::SeekBehavior(sf::Vector2f &target) : targetPosition(target) {}

sf::Vector2f SeekBehavior::calculateSteering(const sf::Vector2f &currentPos,
                                             const sf::Vector2f &currentVel,
                                             float deltaTime) {
  sf::Vector2f desiredVelocity =
      normalize(targetPosition - currentPos) * MAX_VELOCITY;
  sf::Vector2f steering = desiredVelocity - currentVel;
  return steering;
}

sf::Vector2f SeekBehavior::normalize(const sf::Vector2f &v) {
  float length = std::sqrt(v.x * v.x + v.y * v.y);
  if (length != 0) {
    return v / length;
  }
  return v;
}
