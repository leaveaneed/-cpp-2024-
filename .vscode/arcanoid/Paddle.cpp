#include "Paddle.h"

Paddle::Paddle(float width, float height, float speed) : shape(sf::Vector2f(width, height)), speed(speed) {
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(width / 2, height / 2);
}

void Paddle::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && shape.getPosition().x > 0) {
        shape.move(-speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && shape.getPosition().x < 800) {
        shape.move(speed, 0);
    }
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

void Paddle::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
}
