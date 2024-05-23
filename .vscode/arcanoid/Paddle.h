#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle(float width, float height, float speed);

    void update();
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    void setPosition(const sf::Vector2f& position);

private:
    sf::RectangleShape shape;
    float speed;
};

#endif // PADDLE_H
