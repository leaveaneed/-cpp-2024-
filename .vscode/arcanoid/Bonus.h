#pragma once
#include <SFML/Graphics.hpp>

class Bonus {
public:
    Bonus(float x, float y);
    void draw(sf::RenderWindow& window);
    void update();
   

private:
    sf::CircleShape shape;
    
};
