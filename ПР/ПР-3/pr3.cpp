#include <iostream>

#define ll long long

ll add(ll a, ll b);
ll subtract(ll a, ll b);
ll multiply(ll a, ll b);
ll divide(ll a, ll b);

int main() {
    std::cout << "Choose an operation:" << std::endl;
    std::cout << "1. Addition" << std::endl;
    std::cout << "2. Subtraction" << std::endl;
    std::cout << "3. Multiplication" << std::endl;
    std::cout << "4. Division" << std::endl;

    char choice;
    std::cin >> choice;

    ll num1, num2;

    std::cout << "Enter the first number: ";
    std::cin >> num1;

    std::cout << "Enter the second number: ";
    std::cin >> num2;

    ll result;

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

ll add(ll a, ll b) {
    return a + b;
}

ll subtract(ll a, ll b) {
    return a - b;
}

ll multiply(ll a, ll b) {
    return a * b;
}

ll divide(ll a, ll b) {
    if (b == 0) {
        std::cerr << "Error: division by zero" << std::endl;
        return 0;
    }
    return a / b;
}
