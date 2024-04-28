#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <cmath>
#include <optional>

class Student {
private:
    std::string name;
    char mark;
    std::vector<double> ans;

    static char GetMark() {
        int score = rand() % 3 + 3;
        return (score == 3) ? 'C' : (score == 4) ? 'B' : 'A';
    }

    static void InputData(std::ifstream& file, double& a, double& b, double& c, int number) {
        for (int i = 1; i < number; ++i) {
            std::string s;
            std::getline(file, s);
        }
        file >> a >> b >> c;
    }

    static void CalculateRoots(double a, double b, double c, std::vector<double>& ans) {
        double D = b * b - 4 * a * c;
        if (D < 0) {
            ans.clear();
        } else {
            ans.resize(D == 0 ? 1 : 2);
            if (D == 0.0) {
                ans[0] = -b / (2 * a);
            } else {
                ans[0] = (-b + std::sqrt(D)) / (2 * a);
                ans[1] = (-b - std::sqrt(D)) / (2 * a);
            }
        }
    }

public:
    Student(const std::string& _name, int number) : name(_name) {
        mark = GetMark();
        GetAnswers(mark, number);
    }

    void GetAnswers(char mark, int number) {
        if (mark == 'A') {
            std::ifstream file("input.txt");
            double a, b, c;
            InputData(file, a, b, c, number);
            file.close();
            CalculateRoots(a, b, c, ans);
        } else if (mark == 'C') {
            ans = {0};
        } else if (mark == 'B') {
            int chance = rand() % 20 + 1;
            if (chance <= 11) {
                std::ifstream file("input.txt");
                double a, b, c;
                InputData(file, a, b, c, number);
                file.close();
                CalculateRoots(a, b, c, ans);
            } else {
                ans = {0};
            }
        }
    }

    void PrintResults(int number) {
        std::cout << "Number: " << number << std::endl;
        std::cout << name << std::endl;
        if (ans.empty()) {
            std::cout << "No roots found." << std::endl;
        } else {
            for (double root : ans) {
                std::cout << root << std::endl;
            }
        }
    }
};

void Program() {
    std::string name;
    int number;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter assignment number: ";
    std::cin >> number;
    Student student(name, number);
    student.PrintResults(number);
}

int main() {
    srand(time(nullptr)); // Initialize random seed once

    char anotherAttempt;
    do {
        Program();
        std::cout << "Do you want to try another student/number? (y/n): ";
        std::cin >> anotherAttempt;
    } while (anotherAttempt == 'y');

    return 0;
}
