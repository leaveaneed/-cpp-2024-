#include "Paddle.h"

Paddle::Paddle(float x, float y) {
    shape.setPosition(x, y);
    shape.setSize({100.f, 20.f}); 
    shape.setFillColor(sf::Color::Red);
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
