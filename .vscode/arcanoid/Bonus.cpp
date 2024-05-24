#include "Bonus.h"

Bonus::Bonus(float x, float y) {
    shape.setPosition(x, y);
    shape.setRadius(10.f); 
    shape.setFillColor(sf::Color::Green);
}

void Bonus::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Bonus::update() {

    shape.move(0.f, 1.f);
}
