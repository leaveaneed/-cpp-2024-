#include "Block.h"

Block::Block(float x, float y, float width, float height) {
    shape.setPosition(x, y);
    shape.setSize({width, height});
    shape.setFillColor(sf::Color::Blue);
}

void Block::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
