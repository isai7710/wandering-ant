#pragma once
#include "Ant.h"
#include <SFML/Graphics.hpp>
#include <vector>

class World {
public:
  World(unsigned int width, unsigned int height);
  void update(float deltaTime);
  void draw(sf::RenderWindow &window);

private:
  void setupAnts(); // set up Ants vector with number of ants
  std::vector<Ant> ants;

  unsigned int width;
  unsigned int height;
  static constexpr int numAnts = 1;
};
