#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <limits>
#include <cctype>
#include "ring_list.h"
#include "bigint.h"

// Безопасный ввод целого числа с проверкой
int safeGetInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        bool valid = true;
        if (input.empty()) valid = false;
        else {
            size_t start = 0;
            if (input[0] == '-') {
                if (input.size() == 1) valid = false;
                else start = 1;
            }
            for (size_t i = start; i < input.size() && valid; ++i) {
                if (!std::isdigit(static_cast<unsigned char>(input[i]))) valid = false;
            }
        }
        if (!valid) {
            std::cout << "Ошибка! Введите целое число.\n";
            continue;
        }
        try {
            value = std::stoi(input);
            return value;
        }
        catch (...) {
            std::cout << "Ошибка! Слишком большое число.\n";
        }
    }
}

// Основная функция поиска решения A+B=C в кольце цифр
bool solveRing(const std::string& digits, std::string& output) {
    RingList ring;
    ring.buildFromString(digits);
    int N = ring.getSize();
    if (N < 3) return false;

    for (int startPos = 0; startPos < N; ++startPos) {
        Node* startNode = ring.getNode(startPos);
        std::string linear = ring.getSubstring(startNode, N);
        for (int len1 = 1; len1 <= N - 2; ++len1) {
            // Вариант 1: len1 <= len2, длина суммы = len2
            if ((N - len1) % 2 == 0) {
                int len2 = (N - len1) / 2;
                int len3 = N - len1 - len2;
                if (len2 >= len1 && len3 == len2) {
                    std::string a = linear.substr(0, len1);
                    std::string b = linear.substr(len1, len2);
                    std::string c = linear.substr(len1 + len2, len3);
                    if (RingList::isValidNumber(a) && RingList::isValidNumber(b) && RingList::isValidNumber(c)) {
                        if (add(a, b) == c) {
                            output = a + "+" + b + "=" + c;
                            return true;
                        }
                    }
                }
            }
            // Вариант 2: len1 <= len2, длина суммы = len2+1
            if ((N - len1 - 1) % 2 == 0) {
                int len2 = (N - len1 - 1) / 2;
                int len3 = N - len1 - len2;
                if (len2 >= len1 && len3 == len2 + 1) {
                    std::string a = linear.substr(0, len1);
                    std::string b = linear.substr(len1, len2);
                    std::string c = linear.substr(len1 + len2, len3);
                    if (RingList::isValidNumber(a) && RingList::isValidNumber(b) && RingList::isValidNumber(c)) {
                        if (add(a, b) == c) {
                            output = a + "+" + b + "=" + c;
                            return true;
                        }
                    }
                }
            }
            // Вариант 3: len1 > len2, длина суммы = len1
            int len2 = N - 2 * len1;
            if (len2 > 0 && len2 < len1) {
                int len3 = N - len1 - len2;
                if (len3 == len1) {
                    std::string a = linear.substr(0, len1);
                    std::string b = linear.substr(len1, len2);
                    std::string c = linear.substr(len1 + len2, len3);
                    if (RingList::isValidNumber(a) && RingList::isValidNumber(b) && RingList::isValidNumber(c)) {
                        if (add(a, b) == c) {
                            output = a + "+" + b + "=" + c;
                            return true;
                        }
                    }
                }
            }
            // Вариант 4: len1 > len2, длина суммы = len1+1
            len2 = N - 2 * len1 - 1;
            if (len2 > 0 && len2 < len1) {
                int len3 = N - len1 - len2;
                if (len3 == len1 + 1) {
                    std::string a = linear.substr(0, len1);
                    std::string b = linear.substr(len1, len2);
                    std::string c = linear.substr(len1 + len2, len3);
                    if (RingList::isValidNumber(a) && RingList::isValidNumber(b) && RingList::isValidNumber(c)) {
                        if (add(a, b) == c) {
                            output = a + "+" + b + "=" + c;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Главная функция
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned>(time(nullptr)));

    int choice;
    do {
        system("cls");
        std::cout << "\n=== Числовое кольцо (A+B=C) ===\n";
        std::cout << "1. Ввод с клавиатуры\n";
        std::cout << "2. Ввод из файла\n";
        std::cout << "3. Случайная генерация\n";
        std::cout << "0. Выход\n";
        choice = safeGetInt("Выберите способ: ");
        if (choice == 0) break;

        std::string digits;
        bool ok = true;

        switch (choice) {
        case 1: {
            std::cout << "Введите строку цифр (без пробелов): ";
            std::cin >> digits;
            for (char c : digits) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    std::cout << "Ошибка! Можно вводить только цифры.\n";
                    ok = false;
                    break;
                }
            }
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            break;
        }
        case 2: {
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;
            std::cin.ignore();
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cout << "Ошибка открытия файла.\n";
                ok = false;
                break;
            }
            std::getline(file, digits);
            file.close();
            // Удаляем возможные пробелы и переводы строк
            size_t first = digits.find_first_not_of(" \t\n\r");
            if (first != std::string::npos) digits = digits.substr(first);
            size_t last = digits.find_last_not_of(" \t\n\r");
            if (last != std::string::npos) digits = digits.substr(0, last + 1);
            break;
        }
        case 3: {
            int len = safeGetInt("Введите длину строки (1..1000): ");
            if (len < 1 || len > 1000) {
                std::cout << "Некорректная длина.\n";
                ok = false;
                break;
            }
            digits.clear();
            for (int i = 0; i < len; ++i)
                digits.push_back('0' + (rand() % 10));
            std::cout << "Сгенерирована строка: " << digits << "\n";
            break;
        }
        default:
            std::cout << "Неверный выбор.\n";
            ok = false;
        }

        if (!ok) {
            std::cout << "\nНажмите Enter...";
            std::cin.get();
            continue;
        }

        if (digits.empty()) {
            std::cout << "No\n";
        }
        else {
            std::string output;
            if (solveRing(digits, output))
                std::cout << output << "\n";
            else
                std::cout << "No\n";
        }
        std::cout << "\nНажмите Enter...";
        std::cin.get();
    } while (true);

    std::cout << "Программа завершена.\n";
    return 0;
}