#include <SFML/Graphics.hpp> // Подключение заголовочного файла SFML для работы с графикой
#include <iostream> // Подключение заголовочного файла для стандартного ввода/вывода
#include <vector> // Подключение заголовочного файла для работы с векторами
#include <ctime> // Подключение заголовочного файла для работы со временем
#include <cmath> // Подключение заголовочного файла для работы с математическими функциями

const int WINDOW_WIDTH = 384; // Ширина окна
const int WINDOW_HEIGHT = 384; // Высота окна
const int BOARD_SIZE = 6; // Размер доски
const int GEM_SIZE = 64; // Размер гема
const float ANIMATION_DURATION = 0.3f; // Продолжительность анимации в секундах

// Структура, представляющая гем
struct Gem {
    sf::Sprite sprite; // Спрайт гема
    int row; // Номер строки на доске
    int col; // Номер столбца на доске
    bool isMatched; // Флаг, указывающий, совпадает ли гем с другими
    sf::Vector2f startPosition; // Начальная позиция гема
    sf::Vector2f targetPosition; // Целевая позиция гема
    float animationProgress; // Прогресс анимации перемещения гема
};

// Инициализация доски с гемами
void initializeBoard(Gem board[][BOARD_SIZE], const sf::Texture& texture) {
    std::srand(static_cast<unsigned>(std::time(0))); // Установка seed для генерации случайных чисел
    for (int i = 0; i < BOARD_SIZE; ++i) { // Перебор строк доски
        for (int j = 0; j < BOARD_SIZE; ++j) { // Перебор столбцов доски
            int textureIndex = std::rand() % 4; // Генерация случайного индекса для текстуры гема
            sf::IntRect textureRect(textureIndex * GEM_SIZE, 0, GEM_SIZE, GEM_SIZE); // Определение прямоугольника текстуры гема
            board[i][j].sprite.setTexture(texture); // Установка текстуры гема
            board[i][j].sprite.setTextureRect(textureRect); // Установка прямоугольника текстуры для гема
            board[i][j].sprite.setPosition(j * GEM_SIZE, i * GEM_SIZE); // Установка позиции гема на доске
            board[i][j].row = i; // Установка номера строки для гема
            board[i][j].col = j; // Установка номера столбца для гема
            board[i][j].isMatched = false; // Установка флага совпадения гема в false
            board[i][j].startPosition = board[i][j].sprite.getPosition(); // Установка начальной позиции гема
            board[i][j].targetPosition = board[i][j].sprite.getPosition(); // Установка целевой позиции гема
            board[i][j].animationProgress = 1.0f; // Установка прогресса анимации в 1.0 (гем на месте)
        }
    }
}

// Отрисовка доски с гемами на окне
void drawBoard(sf::RenderWindow& window, Gem board[][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) { // Перебор строк доски
        for (int j = 0; j < BOARD_SIZE; ++j) { // Перебор столбцов доски
            window.draw(board[i][j].sprite); // Отрисовка спрайта гема
        }
    }
}

// Проверка, является ли указанная позиция в пределах доски
bool isValidPosition(int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE); // Возвращает true, если позиция в пределах доски
}

// Обмен местами двух гемов на доске
void swapGems(Gem& gem1, Gem& gem2) {
    // Установка начальных и целевых позиций для анимации
    gem1.startPosition = gem1.sprite.getPosition();
    gem2.startPosition = gem2.sprite.getPosition();
    gem1.targetPosition = gem2.startPosition;
    gem2.targetPosition = gem1.startPosition;

    // Сброс прогресса анимации
    gem1.animationProgress = 0.0f;
    gem2.animationProgress = 0.0f;

    // Обмен строк и столбцов между гемами
    int tempRow = gem1.row;
    int tempCol = gem1.col;
    gem1.row = gem2.row;
    gem1.col = gem2.col;
    gem2.row = tempRow;
    gem2.col = tempCol;
}

// Проверка совпадений гемов на доске
void checkMatches(Gem board[][BOARD_SIZE]) {
    // Сброс флагов совпадений для всех гемов на доске
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j].isMatched = false;
        }
    }

    // Проверка горизонтальных совпадений
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE - 2; ++j) {
            if (board[i][j].sprite.getTextureRect() == board[i][j + 1].sprite.getTextureRect() &&
                board[i][j].sprite.getTextureRect() == board[i][j + 2].sprite.getTextureRect()) {
                board[i][j].isMatched = true;
                board[i][j + 1].isMatched = true
;
                board[i][j + 2].isMatched = true;
            }
        }
    }

    // Проверка вертикальных совпадений
    for (int j = 0; j < BOARD_SIZE; ++j) {
        for (int i = 0; i < BOARD_SIZE - 2; ++i) {
            if (board[i][j].sprite.getTextureRect() == board[i + 1][j].sprite.getTextureRect() &&
                board[i][j].sprite.getTextureRect() == board[i + 2][j].sprite.getTextureRect()) {
                board[i][j].isMatched = true;
                board[i + 1][j].isMatched = true;
                board[i + 2][j].isMatched = true;
            }
        }
    }
}

// Удаление совпадений и обновление доски
void removeMatches(Gem board[][BOARD_SIZE], const sf::Texture& texture) {
    for (int j = 0; j < BOARD_SIZE; ++j) { // Перебор столбцов доски
        int emptyRow = BOARD_SIZE - 1; // Начало с нижней строки
        for (int i = BOARD_SIZE - 1; i >= 0; --i) { // Перебор строк в столбце сверху вниз
            if (!board[i][j].isMatched) { // Если гем не совпадает, его нужно опустить
                if (i != emptyRow) { // Если это не пустая строка, нужно выполнить перемещение гема вниз
                    board[emptyRow][j].sprite.setTextureRect(board[i][j].sprite.getTextureRect()); // Установка текстуры для гема
                    board[emptyRow][j].isMatched = false; // Сброс флага совпадения
                    board[emptyRow][j].startPosition = board[emptyRow][j].sprite.getPosition(); // Установка начальной позиции гема
                    board[emptyRow][j].targetPosition = sf::Vector2f(j * GEM_SIZE, emptyRow * GEM_SIZE); // Установка целевой позиции гема
                    board[emptyRow][j].animationProgress = 0.0f; // Сброс прогресса анимации
                }
                emptyRow--; // Переход к следующей пустой строке
            }
        }
        // Заполнение оставшихся строк новыми гемами
        for (int i = emptyRow; i >= 0; --i) { // Заполнение строк начиная с верхних пустых строк
            int textureIndex = std::rand() % 4; // Генерация случайного индекса для текстуры гема
            sf::IntRect textureRect(textureIndex * GEM_SIZE, 0, GEM_SIZE, GEM_SIZE); // Определение прямоугольника текстуры гема
            board[i][j].sprite.setTexture(texture); // Установка текстуры для гема
            board[i][j].sprite.setTextureRect(textureRect); // Установка прямоугольника текстуры для гема
            board[i][j].isMatched = false; // Сброс флага совпадения
            board[i][j].startPosition = sf::Vector2f(j * GEM_SIZE, i * GEM_SIZE - GEM_SIZE * BOARD_SIZE); // Установка начальной позиции гема (выше верхней грани доски)
            board[i][j].targetPosition = sf::Vector2f(j * GEM_SIZE, i * GEM_SIZE); // Установка целевой позиции гема (верхняя грань доски)
            board[i][j].animationProgress = 0.0f; // Сброс прогресса анимации
        }
    }
}

// Обновление доски
void updateBoard(Gem board[][BOARD_SIZE], const sf::Texture& texture) {
    while (true) { // Бесконечный цикл для проверки и удаления совпадений
        checkMatches(board); // Проверка на совпадения гемов
        bool hasMatches = false; // Флаг наличия совпадений
        for (int i = 0; i < BOARD_SIZE; ++i) { // Перебор строк доски
            for (int j = 0; j < BOARD_SIZE; ++j) { // Перебор столбцов доски
                if (board[i][j].isMatched) { // Если гем совпадает с другими
                    hasMatches = true; // Установка флага совпадений в true
                    break; // Выход из цикла
                }
            }
            if (hasMatches) break; // Выход из внешнего цикла, если были найдены совпадения
        }
        if (!hasMatches) break; // Выход из бесконечного цикла, если больше нет совпадений
        removeMatches(board, texture); // Удаление совпадений и обновление доски
    }
}

// Обновление анимаций перемещения гемов
void updateAnimations(Gem board[][BOARD_SIZE], float deltaTime) {
    for (int i = 0; i < BOARD_SIZE; ++i) { // Перебор строк доски
        for (int j = 0; j < BOARD_SIZE; ++j) { // Перебор столбцов доски
            if (board[i][j].animationProgress < 1.0f && board[i][j].targetPosition != board[i][j].startPosition) { // Проверка, что анимация еще не завершена и есть целевая позиция для анимации
                board[i][j].animationProgress += deltaTime / ANIMATION_DURATION; // Обновление прогресса анимации
                if (board[i][j].animationProgress > 1.0f) { // Проверка завершения анимации
                    board[i][j].animationProgress = 1.0f; // Завершение анимации (прогресс = 1)
                }
                float t = board[i][j].animationProgress; // Вычисление текущего прогресса анимации
                board[i][j].sprite.setPosition(
                    board[i][j].startPosition * (1.0f - t) + board[i][j].targetPosition * t
                ); // Интерполяция между начальной и целевой позициями гема для создания анимации перемещения
            }
        }
    }
}

// Главная функция
int main() {
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GEMS");

    // Загрузка текстуры фона
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/leoni/projects/labs/.vscode/gems/images/background.png")) {
        std::cerr << "Failed to load background texture." << std::endl;
        return -1;
    }
    sf::Sprite background(backgroundTexture);

    // Загрузка текстуры гемов
    sf::Texture gemTexture;
    if (!gemTexture.loadFromFile("C:/Users/leoni/projects/labs/.vscode/gems/images/gems.png")) {
        std::cerr << "Failed to load gem texture." << std::endl;
        return -1;
    }

    // Инициализация доски
    Gem board[BOARD_SIZE][BOARD_SIZE];
    initializeBoard(board, gemTexture);

    // Переменная для выбранного гема
    Gem* selectedGem = nullptr;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    int row = mousePosition.y / GEM_SIZE;
                    int col = mousePosition.x / GEM_SIZE;

                    if (isValidPosition(row, col)) {
                        if (selectedGem == nullptr) {
                            selectedGem = &board[row][col];
                        } else {
                            if ((abs(selectedGem->row - row) == 1 && selectedGem->col == col) ||
                                (abs(selectedGem->col - col) == 1 && selectedGem->row == row)) {
                                swapGems(*selectedGem, board[row][col]);
                                updateBoard(board, gemTexture);
                            }
                            selectedGem = nullptr;
                        }
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds(); // Получение прошедшего времени с последнего обновления в секундах

        // Обновление анимаций
        updateAnimations(board, deltaTime);

        window.clear();
        window.draw(background);
        drawBoard(window, board);
        window.display();
    }

    return 0;
}
