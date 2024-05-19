#include <iostream>
#include <cstdlib>
#include <ctime>

const int FIELD_SIZE = 8;
const char COLORS[] = {'R', 'G', 'B', 'Y', 'O'}; // Различные цвета

// Структура представляет квадрат на игровом поле
struct Square {
    char color;
    bool bonus;

    Square() {
        color = COLORS[rand() % 5];
        bonus = false;
    }
};

// Функция для проверки, существует ли комбинация квадратов одного цвета
bool checkCombination(Square field[][FIELD_SIZE]) {
    bool found = false;

    // Проверка по горизонтали
    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE - 2; ++j) {
            if (field[i][j].color == field[i][j + 1].color && field[i][j].color == field[i][j + 2].color) {
                found = true;
                field[i][j].bonus = true;
                field[i][j + 1].bonus = true;
                field[i][j + 2].bonus = true;
            }
        }
    }

    // Проверка по вертикали
    for (int j = 0; j < FIELD_SIZE; ++j) {
        for (int i = 0; i < FIELD_SIZE - 2; ++i) {
            if (field[i][j].color == field[i + 1][j].color && field[i][j].color == field[i + 2][j].color) {
                found = true;
                field[i][j].bonus = true;
                field[i + 1][j].bonus = true;
                field[i + 2][j].bonus = true;
            }
        }
    }

    return found;
}

// Функция для сдвига квадратов вниз
void shiftDown(Square field[][FIELD_SIZE]) {
    for (int j = 0; j < FIELD_SIZE; ++j) {
        for (int i = FIELD_SIZE - 1; i >= 0; --i) {
            if (field[i][j].bonus) {
                for (int k = i; k > 0; --k) {
                    field[k][j] = field[k - 1][j];
                }
                field[0][j].color = COLORS[rand() % 5];
                field[0][j].bonus = false;
            }
        }
    }
}

// Функция для вывода игрового поля на экран
void printField(Square field[][FIELD_SIZE]) {
    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            std::cout << field[i][j].color << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    srand(time(nullptr));

    Square field[FIELD_SIZE][FIELD_SIZE];

    // Инициализация начального игрового поля
    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            field[i][j] = Square();
        }
    }

    // Игровой цикл
    while (true) {
        printField(field);

        if (!checkCombination(field)) {
            std::cout << "No combinations found." << std::endl;
            break;
        }

        std::cout << "Combination found!" << std::endl;

        shiftDown(field);

        std::cout << "Field after shifting:" << std::endl;
        printField(field);
    }

    return 0;
}
