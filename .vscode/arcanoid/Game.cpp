#include "Game.h"

Game::Game() 
    : window(sf::VideoMode(800, 600), "Arkanoid"), 
      paddle(100, 20, 10), 
      ball(10, 5), 
      score(0), 
      lives(3) {
    paddle.setPosition(sf::Vector2f(400, 550));
    ball.setPosition(sf::Vector2f(400, 300));

    // Инициализация блоков и бонусов
    // blocks.push_back(std::make_unique<UnbreakableBlock>(...));
    // blocks.push_back(std::make_unique<BonusBlock>(...));
    // bonuses.push_back(std::make_unique<ResizePaddleBonus>(...));
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    // Обработка событий
}

void Game::update() {
    // Обновление логики игры
}

void Game::render() {
    window.clear();
    // Отрисовка объектов
    window.display();
}
