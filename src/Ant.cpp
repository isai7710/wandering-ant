#include "Ant.h"
#include <cmath>

Ant::Ant(unsigned int windowWidth, unsigned int windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight) {
  triangle.setRadius(antSize);
  triangle.setPointCount(3);

  velocity.x = maxSpeed;
  velocity.y = maxSpeed;
}

void Ant::setPosition(const sf::Vector2f &p) {
  position = sf::Vector2f(p.x, p.y);
  triangle.setPosition(p);
}

sf::Vector2f Ant::getPosition() const {
  return sf::Vector2f(position.x, position.y);
}

void Ant::setVelocity(const sf::Vector2f &v) {
  velocity = sf::Vector2f(v.x, v.y);
}

sf::Vector2f Ant::getVelocity() const {
  return sf::Vector2f(velocity.x, velocity.y);
}

void Ant::update(float deltaTime) { randomMovement(deltaTime); }

void Ant::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(triangle, states);
}

void Ant::randomMovement(float deltaTime) {
  position.x += velocity.x * deltaTime;
  position.y += velocity.y * deltaTime;

  // Boundary checking with window dimensions
  if (position.x > windowWidth || position.x < 0) {
    velocity.x *= -1;
    position.x = std::max(0.0f, std::min((float)windowWidth, position.x));
    desiredDirection.x *= -1; // Change desired direction too
  }
  if (position.y > windowHeight || position.y < 0) {
    velocity.y *= -1;
    position.y = std::max(0.0f, std::min((float)windowHeight, position.y));
    desiredDirection.y *= -1; // Change desired direction too
  }

  triangle.setPosition(position);
};

// ----- UTILITY FUNCTIONS -----
sf::Vector2f Ant::clampVector(const sf::Vector2f &v, float maxValue) {
  float magnitude = std::sqrt(v.x * v.x + v.y * v.y);
  if (magnitude > maxValue) {
    return v * (maxValue / magnitude);
  }
  return v;
}

sf::Vector2f Ant::normalize(const sf::Vector2f &v) {
  float length = std::sqrt(v.x * v.x + v.y * v.y);
  if (length != 0) {
    return v / length;
  }
  return v; // Return unchanged if length is 0
}

float Ant::magnitude(sf::Vector2f v) {
  return std::sqrt(v.x * v.x + v.y * v.y);
}
