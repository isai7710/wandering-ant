#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/System/Vector2.hpp>

class Ant : public sf::Drawable {
public:
  Ant(unsigned int windowWidth, unsigned int windowHeight);

  // Delete copy operations
  Ant(const Ant &) = delete;
  Ant &operator=(const Ant &) = delete;

  // Enable move operations
  Ant(Ant &&) = default;
  // Ant &operator=(Ant &&) = default;

  void setPosition(const sf::Vector2f &p);
  void setVelocity(const sf::Vector2f &v);
  sf::Vector2f getPosition() const { return position; };
  sf::Vector2f getVelocity() const { return velocity; };
  void update(float deltaTime);

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
  void updateVisuals();
  void handleBoundaryCollision();

  sf::ConvexShape triangle;
  sf::VertexArray directionLine;

  sf::Vector2f position;
  sf::Vector2f velocity;

  static constexpr float antSize = 7.f;
  static constexpr float maxSpeed = 100.f;

  const unsigned int windowWidth;
  const unsigned int windowHeight;

  sf::Vector2f clampVector(const sf::Vector2f &v, float maxValue);
  sf::Vector2f normalize(const sf::Vector2f &v);
  float magnitude(sf::Vector2f);
};
