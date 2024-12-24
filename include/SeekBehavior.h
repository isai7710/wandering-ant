#pragma once
#include "IMovementBehavior.h"
#include <SFML/System/Vector2.hpp>

class SeekBehavior : public IMovementBehavior {
public:
  SeekBehavior();
  SeekBehavior(sf::Vector2f &pos);

  sf::Vector2f calculateMovement(const sf::Vector2f &currentPos,
                                 const sf::Vector2f &currentVel,
                                 float deltaTime) override;

private:
  sf::Vector2f targetPosition;
  static constexpr float MAX_VELOCITY = 100.f;
  static constexpr float MAX_ACCELERATION = 100.f;

  // Utility functions
  sf::Vector2f normalize(const sf::Vector2f &v);
};
