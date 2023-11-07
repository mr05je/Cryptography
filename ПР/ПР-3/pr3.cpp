#include <iostream>
#include <string>
#include <algorithm>

std::string add(std::string a, std::string b);
std::string subtract(std::string a, std::string b);
std::string multiply(std::string a, std::string b);
std::string divide(std::string a, std::string b);

int main() {
    std::cout << "Choose an operation:" << std::endl;
    std::cout << "1. Addition" << std::endl;
    std::cout << "2. Subtraction" << std::endl;
    std::cout << "3. Multiplication" << std::endl;
    std::cout << "4. Division" << std::endl;

    char choice;
    std::cin >> choice;

    if (choice != '1' && choice != '2' && choice != '3' && choice != '4')
    {
        std::cerr << "Error: Invalid operation choice" << std::endl;
        return 1;
    }

    std::string num1, num2;

    std::cout << "Enter the first number: ";
    std::cin >> num1;

    std::cout << "Enter the second number: ";
    std::cin >> num2;

    std::string result;

    switch (choice) {
        case '1':
            result = add(num1, num2);
            break;
        case '2':
            result = subtract(num1, num2);
            break;
        case '3':
            result = multiply(num1, num2);
            break;
        case '4':
            result = divide(num1, num2);
            break;
        default:
            std::cerr << "Error: Invalid operation choice" << std::endl;
            return 1;
    }

    std::cout << "Result of the operation: " << result << std::endl;

    return 0;
}

std::string add(std::string a, std::string b) {
    std::string result;
    int carry = 0;

    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int x = (i >= 0) ? a[i] - '0' : 0;
        int y = (j >= 0) ? b[j] - '0' : 0;

        int sum = x + y + carry;
        carry = sum / 10;

        result.push_back((sum % 10) + '0');

        if (i >= 0) i--;
        if (j >= 0) j--;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::string subtract(std::string a, std::string b) {
    std::string result;
    int borrow = 0;

    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0) {
        int x = (i >= 0) ? a[i] - '0' : 0;
        int y = (j >= 0) ? b[j] - '0' : 0;

        int diff = x - y - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.push_back(diff + '0');

        if (i >= 0) i--;
        if (j >= 0) j--;
    }

    while (!result.empty() && result.back() == '0')
        result.pop_back();

    std::reverse(result.begin(), result.end());

    if (result.empty()) return "0";

    return result;
}

std::string multiply(std::string a, std::string b) {
    int len1 = a.length();
    int len2 = b.length();

    std::string result(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; i--) {
        int carry = 0;
        int n1 = a[i] - '0';

        for (int j = len2 - 1; j >= 0; j--) {
            int n2 = b[j] - '0';
            int product = n1 * n2 + (result[i + j + 1] - '0') + carry;
            carry = product / 10;
            result[i + j + 1] = (product % 10) + '0';
        }

        result[i] = carry + '0';
    }

    size_t pos = result.find_first_not_of('0');
    if (pos != std::string::npos)
        return result.substr(pos);

    return "0";
}

std::string divide(std::string a, std::string b) {
    std::string quotient;
    std::string remainder = a;
    int len2 = b.length();

    while (remainder.compare(0, len2, a) >= 0) {
        int q = 0;

        while (remainder.compare(0, len2, a) >= 0) {
            remainder = subtract(remainder, a);
            q++;
        }

        quotient += std::to_string(q);
        remainder.erase(0, std::min(remainder.find_first_not_of('0'), remainder.size() - 1));
    }

    if (quotient.empty())
        return "0";

    return quotient;
}
