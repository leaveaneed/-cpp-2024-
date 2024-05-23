#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle(float x, float y); // Конструктор с аргументами
    void draw(sf::RenderWindow& window);


private:
    sf::RectangleShape shape;

};
