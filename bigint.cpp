// bigint.cpp
// Реализация поразрядного сложения строк

#include "bigint.h"
#include <algorithm>

std::string add(const std::string& a, const std::string& b) {
    std::string result;
    int carry = 0;
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        result.push_back(static_cast<char>(sum % 10 + '0'));
        carry = sum / 10;
    }

    std::reverse(result.begin(), result.end());
    return result;
}
