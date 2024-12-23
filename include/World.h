#pragma once
#include "Ant.h"
#include <SFML/Graphics.hpp>
#include <vector>

class World {
public:
  explicit World(unsigned int width, unsigned int height);
  void update(float deltaTime);
  void draw(sf::RenderWindow &window);

private:
  void setupAnts();

  std::vector<Ant> ants;
  unsigned int width;
  unsigned int height;
  static constexpr std::size_t NUM_ANTS = 1;
};
