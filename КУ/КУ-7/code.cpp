#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#pragma region converters
std::vector<int> convertStringToVector(std::string num);
std::string convertVectorToString(std::vector<int> num);
std::string convertVectorToString(std::pair<std::vector<int>, int> num);
int convertVectorToInt(const std::vector<int>& vec);
#pragma endregion

#pragma region calculators
std::vector<int> add(std::vector<int> a, std::vector<int> b);
std::vector<int> subtract(std::vector<int> a, std::vector<int> b);
std::vector<int> multiply(std::vector<int> a, std::vector<int> b);
std::pair<std::vector<int>, int> divide(std::vector<int> a, std::vector<int> b);

int compareVectors(const std::vector<int>& a, const std::vector<int>& b);
#pragma endregion


int main() {
    std::string num1, num2;

    std::cout << "===ADD===" << std::endl;
    std::cout << "Enter the first number: ";
    std::cin >> num1;

    std::cout << "Enter the second number: ";
    std::cin >> num2;

    std::cout << convertVectorToString(add(convertStringToVector(num1), convertStringToVector(num2))) << std::endl;

    std::cout << "===SUBTRACT===" << std::endl;
    std::cout << "Enter the first number: ";
    std::cin >> num1;

    std::cout << "Enter the second number: ";
    std::cin >> num2;
    std::cout << convertVectorToString(subtract(convertStringToVector(num1), convertStringToVector(num2))) << std::endl;

    std::cout << "===MULTIPLY===" << std::endl;
    std::cout << "Enter the first number: ";
    std::cin >> num1;

    std::cout << "Enter the second number: ";
    std::cin >> num2;
    std::cout << convertVectorToString(multiply(convertStringToVector(num1), convertStringToVector(num2))) << std::endl;

    std::cout << "===DIVIDE===" << std::endl;
    std::cout << "Enter the first number: ";
    std::cin >> num1;

    std::cout << "Enter the second number: ";
    std::cin >> num2;
    std::cout << convertVectorToString(divide(convertStringToVector(num1), convertStringToVector(num2))) << std::endl;

    return 0;
}

#pragma region converters
std::vector<int> convertStringToVector(std::string num) {
    std::vector<int> res;

    for (char i : num)
        if (isdigit(i))
            res.push_back(i - '0');

    return res;
}

std::string convertVectorToString(std::vector<int> num) {
    std::string res;

    for (int i = 0; i < num.size(); i++)
        res += std::to_string(num[i]);

    return res;
}

std::string convertVectorToString(std::pair<std::vector<int>, int> num) {
    std::string res;

    res += convertVectorToString(num.first);
    if (num.second == 0) return res;
    res += ".";
    res += std::to_string(num.second);

    return res;
}

int convertVectorToInt(const std::vector<int>& vec) {
    int result = 0;
    for (int i = vec.size() - 1; i >= 0; --i) {
        result = result * 10 + vec[i];
    }
    return result;
}
#pragma endregion

#pragma region calc
std::vector<int> add(std::vector<int> a, std::vector<int> b) {
    std::vector<int> res;
    int t = 0, tt;

    for (size_t i = 0; i < a.size() || i < b.size(); ++i) {
        int a_digit = i < a.size() ? a[i] : 0;
        int b_digit = i < b.size() ? b[i] : 0;

        tt = a_digit + b_digit + t;
        t = 0;
        if (tt >= 10) {
            t++;
            tt -= 10;
        }

        res.push_back(tt);
    }

    if (t != 0) res.insert(res.begin(), t);

    return res;
}

std::vector<int> subtract(std::vector<int> a, std::vector<int> b) {
    std::vector<int> result;
    int borrow = 0;

    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0) {
        int x = (i >= 0) ? a[i] : 0;
        int y = (j >= 0) ? b[j] : 0;

        int diff = x - y - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.push_back(diff);

        if (i >= 0) i--;
        if (j >= 0) j--;
    }

    while (!result.empty() && result.back() == 0)
        result.pop_back();

    std::reverse(result.begin(), result.end());

    if (result.empty()) return {0};

    return result;
}

std::vector<int> multiply(std::vector<int> a, std::vector<int> b) {
    std::vector<int> res(a.size() + b.size(), 0);

    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b.size(); ++j) {
            res[i + j] += a[i] * b[j];
            res[i + j + 1] += res[i + j] / 10;
            res[i + j] %= 10;
        }
    }

    while (res.size() > 1 && res.back() == 0)
        res.pop_back();

    std::rotate(res.rbegin(), res.rbegin() + 1, res.rend());

    return res;
}

std::pair<std::vector<int>, int> divide(std::vector<int> a, std::vector<int> b) {
    std::vector<int> quotient;
    std::vector<int> remainder = a;

    while (compareVectors(remainder, b) >= 0) {
        int q = 0;

        while (compareVectors(remainder, b) >= 0) {
            remainder = subtract(remainder, b);
            q++;
        }

        quotient.push_back(q);
        while (!remainder.empty() && remainder.back() == 0) {
            remainder.pop_back();
        }
    }

    if (quotient.empty()) quotient.push_back(0);

    std::reverse(quotient.begin(), quotient.end());
    return {quotient, convertVectorToInt(remainder)};
}

int compareVectors(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) {
        return a.size() < b.size() ? -1 : 1;
    }
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] != b[i]) {
            return a[i] < b[i] ? -1 : 1;
        }
    }
    return 0;
}

#pragma endregion