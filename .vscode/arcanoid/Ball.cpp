#include "Ball.h"

Ball::Ball(float x, float y) {
    shape.setPosition(x, y);
    shape.setRadius(10.f); // Радиус мяча
    shape.setFillColor(sf::Color::White); // Цвет мяча
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
