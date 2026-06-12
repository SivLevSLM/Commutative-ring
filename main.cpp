#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "ring_list.h"
#include "bigint.h"
#include "validation.h"
#include "node.h" 
#include <windows.h>

bool solveRing(const RingList& ring, std::string& output) {
    int N = ring.getSize();
    if (N < 3) return false;

    for (int startPos = 0; startPos < N; ++startPos) {
        Node* startNode = ring.getNode(startPos);
        std::string linear = ring.getSubstring(startNode, N);

        for (int len1 = 1; len1 <= N - 2; ++len1) {
            // Случай 1: len1 <= len2, len3 = len2
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
            // Случай 2: len1 <= len2, len3 = len2 + 1
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
            // Случай 3: len1 > len2, len3 = len1
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
            // Случай 4: len1 > len2, len3 = len1 + 1
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

void showMenu() {
    std::cout << "\n=== Числовое кольцо (A+B=C) ===\n";
    std::cout << "1. Ввести кольцо с клавиатуры\n";
    std::cout << "2. Загрузить кольцо из файла\n";
    std::cout << "3. Сгенерировать случайное кольцо\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned>(time(nullptr)));
    int choice;
    do {
        showMenu();
        choice = Validation::getIntRange(0, 3);

        RingList ring;
        bool ringReady = false;

        switch (choice) {
        case 1: {
            std::cin.ignore(10000, '\n');
            std::cout << "Введите строку цифр (без пробелов, не более 1000): ";
            std::string digits;
            std::getline(std::cin, digits);
            digits.erase(std::remove_if(digits.begin(), digits.end(), ::isspace), digits.end());
            if (digits.empty()) {
                std::cout << "Ошибка: пустая строка.\n";
                break;
            }
            if (digits.size() > 1000) {
                std::cout << "Ошибка: слишком много цифр (макс. 1000).\n";
                break;
            }
            ring.buildFromString(digits);
            ringReady = true;
            break;
        }
        case 2: {
            std::cin.ignore(10000, '\n');
            std::cout << "Введите имя файла: ";
            std::string fname = Validation::getValidFile();
            std::string content;
            if (!Validation::readFileContent(fname, content)) {
                std::cout << "Ошибка чтения файла или файл пуст.\n";
                break;
            }
            if (content.size() > 1000) {
                std::cout << "Ошибка: слишком много цифр (макс. 1000).\n";
                break;
            }
            ring.buildFromString(content);
            ringReady = true;
            std::cout << "Загружено кольцо: " << content << "\n";
            break;
        }
        case 3: {
            std::cout << "Введите количество цифр (не более 1000): ";
            int n = Validation::getIntRange(1, 1000);
            ring.fillRandom(n);
            ringReady = true;
            std::cout << "Сгенерировано кольцо: " << ring.toString() << "\n";
            break;
        }
        case 0:
            std::cout << "До свидания!\n";
            continue;
        }

        if (ringReady) {
            std::cout << "Кольцо: ";
            ring.print();
            std::string result;
            if (solveRing(ring, result)) {
                std::cout << result << std::endl;
            }
            else {
                std::cout << "No" << std::endl;
            }
        }
    } while (choice != 0);

    return 0;
}