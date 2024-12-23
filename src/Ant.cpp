#include "Ant.h"
#include <cmath>

Ant::Ant(unsigned int windowWidth, unsigned int windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight),
      directionLine(sf::Lines, 2) {
  triangle.setRadius(antSize);
  triangle.setPointCount(3);
  triangle.setOrigin(antSize, antSize);

  velocity.x = maxSpeed;
  velocity.y = maxSpeed;
}

void Ant::setPosition(const sf::Vector2f &p) {
  position = p;
  triangle.setPosition(p);

  directionLine[0].position = position;
}

void Ant::setVelocity(const sf::Vector2f &v) { velocity = v; }

sf::Vector2f Ant::getPosition() const { return position; }
sf::Vector2f Ant::getVelocity() const { return velocity; }

void Ant::update(float deltaTime) {
  randomMovement(deltaTime);

  if (magnitude(velocity) > 0) {
    float angle = atan2(velocity.y, velocity.x) * 180.f / M_PI;
    triangle.setRotation(angle);
  }

  directionLine[0].position = position;
  sf::Vector2f endPoint = position + normalize(velocity) * 20.f;
  directionLine[1].position = endPoint;
}

void Ant::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(triangle, states);
  target.draw(directionLine, states);
}

void Ant::randomMovement(float deltaTime) {
  position += velocity * deltaTime;

  // Boundary checking with window dimensions
  if (position.x > windowWidth || position.x < 0) {
    velocity.x *= -1;
    position.x = std::max(0.0f, std::min((float)windowWidth, position.x));
  }
  if (position.y > windowHeight || position.y < 0) {
    velocity.y *= -1;
    position.y = std::max(0.0f, std::min((float)windowHeight, position.y));
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
