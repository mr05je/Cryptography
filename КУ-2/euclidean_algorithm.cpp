#include <iostream>

int main() {
    int a, b;

    std::cout << "Insert numbers a and b (example: \"24 2\")" << std::endl;
    std::cin >> a >> b;

    std::cout << "GCD of numbers " << a << " and " << b << " = ";

    if (a != b) {
        while (a != 0 && b != 0) {
            if (a > b) {
                a %= b;
            } else {
                b %= a;
            }
        }
        std::cout << a + b;
    } else {
        std::cout << a;
    }

    return 0;
}