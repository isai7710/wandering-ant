#include "Ant.h"
#include <cmath>

Ant::Ant(unsigned int windowWidth, unsigned int windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight),
      directionLine(sf::Lines, 2) {
  triangle.setPointCount(3);
  triangle.setPoint(0, sf::Vector2f(0, -2 * ANT_SIZE));    // Top vertex
  triangle.setPoint(1, sf::Vector2f(-ANT_SIZE, ANT_SIZE)); // Bottom-left vertex
  triangle.setPoint(2, sf::Vector2f(ANT_SIZE, ANT_SIZE)); // Bottom-right vertex

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
  if (movementBehavior) {
    sf::Vector2f steeringAcceleration =
        movementBehavior->calculateSteering(position, velocity, deltaTime);

    // integrate acceleration to change the ants velocity accordingly
    velocity += steeringAcceleration * deltaTime;

    // Clamp ant's velocity to MAX_SPEED to ensure it doesn't go over
    velocity = clampVector(velocity, MAX_SPEED);
  }

  // Update position and handle collisions
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

  float currentVelocityMagnitude = magnitude(velocity);
  if (currentVelocityMagnitude > 0) {
    sf::Vector2f normalizedVelocityDirection =
        velocity / currentVelocityMagnitude;
    float angle = std::atan2(velocity.y, velocity.x);

    triangle.setRotation(angle * 180 / M_PI + 90);
    directionLine[0].position = position;
    directionLine[1].position =
        position + normalizedVelocityDirection * DIRECTION_LINE_LENGTH;
  }
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
