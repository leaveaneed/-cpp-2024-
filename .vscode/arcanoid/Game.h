#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Block.h" 
#include "Bonus.h" 
#include <vector>
#include <memory> 

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    Paddle paddle;
    Ball ball;
    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Bonus>> bonuses;
    int score;
    int lives;
};
