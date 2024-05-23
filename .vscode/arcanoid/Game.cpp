#include "Game.h"


Game::Game()
    : window(sf::VideoMode(800, 600), "Arkanoid"),
      paddle(400.f, 550.f), // Вызов конструктора Paddle с аргументами x и y
      ball(400.f, 300.f) {
    blocks.push_back(std::make_unique<Block>(100.f, 100.f, 60.f, 20.f));
    blocks.push_back(std::make_unique<Block>(200.f, 100.f, 60.f, 20.f));

    
    bonuses.push_back(std::make_unique<Bonus>(150.f, 150.f));
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update() {
    
    for (auto& bonus : bonuses) {
        bonus->update();
    }
}

void Game::render() {
    window.clear();
    paddle.draw(window);
    ball.draw(window);
    for (auto& block : blocks) {
        block->draw(window);
    }
    for (auto& bonus : bonuses) {
        bonus->draw(window);
    }
    window.display();
}
