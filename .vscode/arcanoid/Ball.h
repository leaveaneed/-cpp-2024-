#pragma once
#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball(float x, float y); // Конструктор с аргументами
    void draw(sf::RenderWindow& window);
    

private:
    sf::CircleShape shape;
    
};
