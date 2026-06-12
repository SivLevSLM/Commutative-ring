#pragma once
#include <string>

namespace Validation {
    void clearInput();
    bool isNumber(const std::string& str, bool allowNegative = false);
    int getInt();
    int getIntMin(int minValue);
    int getIntRange(int minValue, int maxValue);
    std::string getValidFile();  // имя существующего файла
    bool readFileContent(const std::string& filename, std::string& content); // читает первую строку без пробелов
}