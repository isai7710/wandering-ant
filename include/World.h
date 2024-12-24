#pragma once
#include "Ant.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class World {
public:
  explicit World(unsigned int width, unsigned int height);
  void update(float deltaTime);
  void draw(sf::RenderWindow &window);
  void updateTarget(sf::Vector2f position);
  sf::Vector2f getTargetPosition();

private:
  void setupAnts();

  sf::CircleShape target{5.0f};
  sf::Vector2f targetPosition;
  bool hasTarget = false;

  void clearTarget();

  std::vector<Ant> ants;
  const unsigned int width;
  const unsigned int height;
  static constexpr std::size_t NUM_ANTS = 3;
};
