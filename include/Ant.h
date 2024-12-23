#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Ant : public sf::Drawable {
public:
  Ant(unsigned int windowWidth, unsigned int windowHeight);
  void setPosition(const sf::Vector2f &p);
  sf::Vector2f getPosition() const;
  void setVelocity(const sf::Vector2f &v);
  sf::Vector2f getVelocity() const;
  void update(float deltaTime);

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  void randomMovement(float deltaTime);

  sf::CircleShape triangle;
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f desiredDirection;

  static constexpr float antSize = 10.f;
  static constexpr float maxSpeed = 100.f;

  unsigned int windowWidth;
  unsigned int windowHeight;

  sf::Vector2f clampVector(const sf::Vector2f &v, float maxValue);
  sf::Vector2f normalize(const sf::Vector2f &v);
  float magnitude(sf::Vector2f);
};
