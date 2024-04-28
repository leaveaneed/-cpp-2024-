#include <iostream>
#include <fstream>
#include <cmath>

// Структура для хранения результата решения квадратного уравнения
struct QuadraticEquationResult {
    bool hasSolution;
    double root1;
    double root2;
};

// Функция для вычисления дискриминанта
double calculateDiscriminant(double a, double b, double c) {
    return b * b - 4 * a * c;
}

// Функция для решения квадратного уравнения
QuadraticEquationResult solveQuadraticEquation(double a, double b, double c) {
    QuadraticEquationResult result;
    double discriminant = calculateDiscriminant(a, b, c);

    // Проверка значений дискриминанта и вычисление корней
    if (discriminant < 0) {
        result.hasSolution = false;
    } else if (discriminant == 0) {
        result.hasSolution = true;
        result.root1 = -b / (2 * a);
    } else {
        result.hasSolution = true;
        result.root1 = (-b + sqrt(discriminant)) / (2 * a);
        result.root2 = (-b - sqrt(discriminant)) / (2 * a);
    }

    return result;
}

// Функция для записи корней уравнения в текстовый файл
bool writeRootsToFile(const std::string& filename, const QuadraticEquationResult& result) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << " для записи" << std::endl;
        return false;
    }

    if (result.hasSolution) {
        if (result.root1 == result.root2) {
            file << "Уравнение имеет единственный корень: " << result.root1 << std::endl;
        } else {
            file << "Уравнение имеет два корня: " << result.root1 << " и " << result.root2 << std::endl;
        }
    } else {
        file << "Уравнение не имеет действительных корней." << std::endl;
    }

    return true;
}

// Основная функция программы
int main() {
    double a, b, c;

    std::cout << "Введите коэффициенты квадратного уравнения (ax^2 + bx + c): ";
    std::cin >> a >> b >> c;

    QuadraticEquationResult result = solveQuadraticEquation(a, b, c);

    std::string filename;
    std::cout << "Введите имя файла для сохранения результатов: ";
    std::cin >> filename;

    if (!writeRootsToFile(filename, result)) {
        return 1; // Произошла ошибка при записи результатов в файл
    }

    return 0;
}
