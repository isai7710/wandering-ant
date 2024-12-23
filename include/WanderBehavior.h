#pragma once
#include "IMovementBehavior.h"
#include <SFML/System/Vector2.hpp>
#include <random>

class WanderBehavior : public IMovementBehavior {
public:
  WanderBehavior();

  sf::Vector2f calculateMovement(const sf::Vector2f &currentPos,
                                 const sf::Vector2f &currentVel,
                                 float deltaTime) override;

  void setWanderRadius(float radius) { wanderRadius = radius; };
  void setWanderDistance(float distance) { wanderDistance = distance; }
  void setWanderJitter(float jitter) { wanderJitter = jitter; };

private:
  sf::Vector2f wanderTarget; // Point on the wander circle
  std::mt19937 rng;          // Random number generator

  // Wander behavior parameters
  float wanderRadius = 50.0f;   // Radius of wander circle
  float wanderDistance = 75.0f; // Distance of wander circle from agent
  float wanderJitter = 7.0f;    // Maximum random displacement

  // Utility functions
  sf::Vector2f getRandomVector();
  sf::Vector2f normalize(const sf::Vector2f &v);
};
