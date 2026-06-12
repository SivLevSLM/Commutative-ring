#include "validation.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <limits>

void Validation::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Validation::isNumber(const std::string& str, bool allowNegative) {
    if (str.empty()) return false;
    size_t start = 0;
    if (allowNegative && str[0] == '-') {
        if (str.size() == 1) return false;
        start = 1;
    }
    for (size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(str[i]))) return false;
    }
    return true;
}

int Validation::getInt() {
    std::string input;
    while (true) {
        std::cin >> input;
        if (!isNumber(input, true)) {
            std::cout << "Ошибка! Введите целое число: ";
            clearInput();
            continue;
        }
        try {
            return std::stoi(input);
        }
        catch (...) {
            std::cout << "Слишком большое число: ";
            clearInput();
        }
    }
}

int Validation::getIntMin(int minValue) {
    while (true) {
        int val = getInt();
        if (val >= minValue) return val;
        std::cout << "Ошибка! Число должно быть >= " << minValue << ": ";
    }
}

int Validation::getIntRange(int minValue, int maxValue) {
    while (true) {
        int val = getInt();
        if (val >= minValue && val <= maxValue) return val;
        std::cout << "Ошибка! Введите число от " << minValue << " до " << maxValue << ": ";
    }
}

std::string Validation::getValidFile() {
    std::string filename;
    while (true) {
        std::cin >> filename;
        std::ifstream test(filename);
        if (!test) {
            std::cout << "Файл не найден. Повторите: ";
            continue;
        }
        test.close();
        return filename;
    }
}

bool Validation::readFileContent(const std::string& filename, std::string& content) {
    std::ifstream file(filename);
    if (!file) return false;
    std::getline(file, content);
    file.close();
    size_t first = content.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        content.clear();
        return false;
    }
    size_t last = content.find_last_not_of(" \t\n\r");
    content = content.substr(first, last - first + 1);
    return !content.empty();
}