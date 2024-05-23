#pragma once
#include <SFML/Graphics.hpp>

class Block {
public:
    Block(float x, float y, float width, float height);
    void draw(sf::RenderWindow& window);
    

private:
    sf::RectangleShape shape;
    
};
