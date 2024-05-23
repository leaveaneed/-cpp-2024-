#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball(float radius, float speed);

    void update();
    void draw(sf::RenderWindow& window);
    void checkCollision(const sf::FloatRect& bounds);

    sf::FloatRect getBounds() const;
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

#endif // BALL_H
