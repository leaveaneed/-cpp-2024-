#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
#include <utility>

class Equation {
public:
    Equation(double a, double b, double c) : a(a), b(b), c(c) {}
    std::pair<double, double> solve() const {
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) return {NULL, NULL};
        double sqrtDiscriminant = std::sqrt(discriminant);
        return {(-b + sqrtDiscriminant) / (2 * a), (-b - sqrtDiscriminant) / (2 * a)};
    }
    std::string toString() const {
        return std::to_string(a) + "x^2 + " + std::to_string(b) + "x + " + std::to_string(c);
    }
private:
    double a, b, c;
};

class Student {
public:
    Student(std::string name) : name(name) {}
    virtual ~Student() {}
    virtual std::pair<double, double> solveEquation(const Equation& eq) const = 0;
    std::string getName() const { return name; }
private:
    std::string name;
};

class GoodStudent : public Student {
public:
    using Student::Student;
    std::pair<double, double> solveEquation(const Equation& eq) const override {
        return eq.solve();
    }
};

class AverageStudent : public Student {
public:
    using Student::Student;
    std::pair<double, double> solveEquation(const Equation& eq) const override {
        if (std::rand() % 100 < 55) {  // 55% вероятность правильного решения
            return eq.solve();
        } else {
            return {NULL, NULL};  // Некорректное решение
        }
    }
};

class BadStudent : public Student {
public:
    using Student::Student;
    std::pair<double, double> solveEquation(const Equation& eq) const override {
        return {0, 0};  // Всегда неверное решение
    }
};

struct Submission {
    Equation equation;
    std::pair<double, double> solution;
    std::string studentName;
};

class Teacher {
public:
    void receiveSubmission(const Submission& submission) {
        submissions.push(submission);
    }

    void evaluateSubmissions() {
        while (!submissions.empty()) {
            Submission submission = submissions.front();
            submissions.pop();

            auto correctSolution = submission.equation.solve();
            if (correctSolution == submission.solution) {
                results[submission.studentName]++;
            }
        }
    }

    void publishResults() const {
        for (const auto& [studentName, score] : results) {
            std::cout << studentName << ": " << score << " correct solutions\n";
        }
    }
private:
    std::queue<Submission> submissions;
    std::map<std::string, int> results;
};

int main() {
    std::srand(std::time(nullptr)); // Инициализация генератора случайных чисел

    // Чтение уравнений из файла (предположим, что файл называется "equations.txt")
    std::ifstream file("equations.txt");
    std::vector<Equation> equations;
    double a, b, c;
    while (file >> a >> b >> c) {
        equations.emplace_back(a, b, c);
    }

// Создание студентов
std::vector<Student*> students = {
    new GoodStudent("Alice"),
    new AverageStudent("Bob"),
    new BadStudent("Charlie"),
    new GoodStudent("David"),
    new AverageStudent("Eve"),
};

    // Преподаватель
    Teacher teacher;

    // Студенты решают задачи и отправляют решения преподавателю
    for (const auto& eq : equations) {
        for (const auto& student : students) {
            teacher.receiveSubmission({eq, student->solveEquation(eq), student->getName()});
        }
    }

    // Преподаватель проверяет решения
    teacher.evaluateSubmissions();

    // Публикация результатов
    teacher.publishResults();

    // Освобождение памяти
    for (auto student : students) {
        delete student;
    }

    return 0;
}
