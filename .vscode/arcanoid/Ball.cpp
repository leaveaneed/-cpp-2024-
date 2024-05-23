#include "Ball.h"

Ball::Ball(float radius, float speed) : shape(radius), velocity(speed, speed) {
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(radius, radius);
}

void Ball::update() {
    shape.move(velocity);

    // Check for wall collisions
    if (shape.getPosition().x <= 0 || shape.getPosition().x >= 800) {
        velocity.x = -velocity.x;
    }
    if (shape.getPosition().y <= 0) {
        velocity.y = -velocity.y;
    }
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

void Ball::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}
