#include <iostream>

double calculateLogarithm(double number);
double pow(double base, int exponent);

int main() {
    int n;
    std::cout << "Insert number, for calculating log: ";
    std::cin >> n;

    std::cout << "Result of log(" << n << ") is " << calculateLogarithm(n) << std::endl;

    return 0;
}

double calculateLogarithm(double number) {
    if (number <= 0) return -1;

    const int ITERATIONS = 1000;
    double result = 0.0;

    for (int i = 0; i < ITERATIONS; i++) {
        double term = (i % 2 == 0 ? 1 : -1) * pow(number - 1, i + 1) / (i + 1);
        result += term;
    }

    return result;
}

double pow(double base, int exponent) {
    if (exponent == 0) return 1;

    double result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}