#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int ts = 64; // Размер тайла
Vector2i offset((ts - 64) / 2, (ts - 64) / 2);

struct Piece {
    int x, y, col, row, kind, match, alpha;
    Piece() : match(0), alpha(255) {}
};

void swap(Piece &p1, Piece &p2) {
    std::swap(p1.col, p2.col);
    std::swap(p1.row, p2.row);
}

int main() {
    srand(time(0));

    RenderWindow app(VideoMode(512, 512), "Game!"); 
    app.setFramerateLimit(60);

    Texture backgroundTexture, gemsTexture; 
    if (!backgroundTexture.loadFromFile("C:/Users/leoni/projects/labs/.vscode/gems/images/background.png") || !gemsTexture.loadFromFile("C:/Users/leoni/projects/labs/.vscode/gems/images/Sprite-0002.png")) {
        return EXIT_FAILURE;
    }

    Sprite background(backgroundTexture);
    background.setScale(512.f / backgroundTexture.getSize().x, 512.f / backgroundTexture.getSize().y); // Масштабируем фон до размеров окна

    Piece grid[10][10];

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            grid[i][j].kind = rand() % 3;
            grid[i][j].col = j;
            grid[i][j].row = i;
            grid[i][j].x = j * ts;
            grid[i][j].y = i * ts;
        }
    }

    int x0, y0, x, y;
    int click = 0;
    Vector2i pos;
    bool isSwap = false, isMoving = false;

    // Создание спрайтов для каждого типа гема
    Sprite gemSprites[3];
    for (int i = 0; i < 3; ++i) {
        gemSprites[i].setTexture(gemsTexture);
        gemSprites[i].setTextureRect(IntRect(i * 64, 0, 64, 64)); // каждый гем 64x64
    }

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (!isSwap && !isMoving) {
                        click++;
                    }
                    pos = Mouse::getPosition(app) - offset;
                }
                
        }
        

        
        // Обработка клика мыши
        if (click == 1) {
            x0 = pos.x / ts + 1;
            y0 = pos.y / ts + 1;
        }
        if (click == 2) {
            x = pos.x / ts + 1;
            y = pos.y / ts + 1;
            if (abs(x - x0) + abs(y - y0) == 1) {
                swap(grid[y0][x0], grid[y][x]);
                isSwap = true;
                click = 0;
            } else {
                click = 1;
            }
        }

        // Поиск совпадений
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                if (grid[i][j].kind == grid[i + 1][j].kind && grid[i][j].kind == grid[i - 1][j].kind) {
                    for (int n = -1; n <= 1; n++) {
                        grid[i + n][j].match++;
                    }
                }

                if (grid[i][j].kind == grid[i][j + 1].kind && grid[i][j].kind == grid[i][j - 1].kind) {
                    for (int n = -1; n <= 1; n++) {
                        grid[i][j + n].match++;
                    }
                }
            }
        }

        // Анимация движения
        isMoving = false;
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                Piece &p = grid[i][j];
                int dx, dy;
                for (int n = 0; n < 4; n++) {   // 4 - скорость
                    dx = p.x - p.col * ts;
                    dy = p.y - p.row * ts;
                    if (dx) p.x -= dx / abs(dx);
                    if (dy) p.y -= dy / abs(dy);
                }
                if (dx || dy) isMoving = true;
            }
        }

        // Анимация удаления
        if (!isMoving) {
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    if (grid[i][j].match) {
                        if (grid[i][j].alpha > 10) {
                            grid[i][j].alpha -= 10;
                            isMoving = true;
                        }
                    }
                }
            }
        }

        // Получение очков
        int score = 0;
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                score += grid[i][j].match;
            }
        }

        // Вторая смена, если нет совпадений
        if (isSwap && !isMoving) {
            if (!score) {
                swap(grid[y0][x0], grid[y][x]);
            }
            isSwap = false;
        }

        // Обновление сетки
        if (!isMoving) {
            for (int i = 8; i > 0; i--) {
                for (int j = 1; j <= 8; j++) {
                    if (grid[i][j].match) {
                        for (int n = i; n > 0; n--) {
                            if (!grid[n][j].match) {
                                swap(grid[n][j], grid[i][j]);
                                break;
                            }
                        }
                    }
                }
            }

            for (int j = 1; j <= 8; j++) {
                for (int i = 8, n = 0; i > 0; i--) {
                    if (grid[i][j].match) {
                        grid[i][j].kind = rand() % 3; // Осторожно, здесь происходит возврат к рандомизации 3-х типов гемов
                        grid[i][j].y = -ts * n++;
                        grid[i][j].match = 0;
                        grid[i][j].alpha = 255;
                    }
                }
            }
        }

        // Отрисовка
        app.draw(background);

        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                Piece p = grid[i][j];
                gemSprites[p.kind].setColor(Color(255, 255, 255, p.alpha)); // Обращаемся к массиву спрайтов по типу гема
                gemSprites[p.kind].setPosition(p.x, p.y);
                gemSprites[p.kind].move(offset.x - ts, offset.y - ts);
                app.draw(gemSprites[p.kind]);
            }
        }

        app.display();
    }

    return 0;
}

