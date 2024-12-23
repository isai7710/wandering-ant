#include "Ant.h"
#include <cmath>

Ant::Ant(unsigned int windowWidth, unsigned int windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight),
      directionLine(sf::Lines, 2) {
  triangle.setPointCount(3);
  triangle.setPoint(0, sf::Vector2f(0, -2 * antSize));   // Top vertex
  triangle.setPoint(1, sf::Vector2f(-antSize, antSize)); // Bottom-left vertex
  triangle.setPoint(2, sf::Vector2f(antSize, antSize));  // Bottom-right vertex

  directionLine[0].color = sf::Color::Yellow;
  directionLine[1].color = sf::Color::Yellow;
}

void Ant::setPosition(const sf::Vector2f &p) {
  position = p;
  triangle.setPosition(p);

  directionLine[0].position = position;
}

void Ant::setVelocity(const sf::Vector2f &v) { velocity = v; }

void Ant::update(float deltaTime) {
  position += velocity * deltaTime;
  handleBoundaryCollision();
  updateVisuals();
}

void Ant::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(triangle, states);
  target.draw(directionLine, states);
}

void Ant::handleBoundaryCollision() {
  if (position.x > windowWidth || position.x < 0) {
    velocity.x *= -1;
    position.x = std::clamp(position.x, 0.f, static_cast<float>(windowWidth));
  }
  if (position.y > windowHeight || position.y < 0) {
    velocity.y *= -1;
    position.y = std::clamp(position.y, 0.f, static_cast<float>(windowHeight));
  }
}

void Ant::updateVisuals() {
  triangle.setPosition(position);

  if (magnitude(velocity) > 0) {
    float angle = std::atan2(velocity.y, velocity.x);
    triangle.setRotation(angle * 180.f / M_PI + 90);
  }

  directionLine[0].position = position;
  sf::Vector2f normalized = velocity;
  if (magnitude(velocity) > 0) {
    normalized /= magnitude(velocity);
  }
  directionLine[1].position = position + normalized * 30.f;
}

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
