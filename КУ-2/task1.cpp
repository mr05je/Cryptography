#include <iostream>

int mod(int a, int b) {
    const auto p = a / b;

    const auto mod = a - b * p;

    return mod;
}

int main() {
    std::cout << "Insert 2 numbers to calculate mod" << std::endl;

    int a, b;

    std::cin >> a >> b;

    std::cout << "In-Built operator %: " << a << " % " << b << " = " << a % b << std::endl;
    std::cout << "Self wrote mod func: " << a << " % " << b << " = " << mod(a, b) << std::endl;

    return 0;
}