#include <iostream>
#include <vector>

std::vector<int> sieveOfEratosthenes(int n);
std::vector<long long> fibonacci(int n);

int main() {
    int n;
    std::cout << "Sieve of Eratosthenes:" << std::endl << "Enter the maximum number to search for primes: ";
    std::cin >> n;

    std::vector<int> primes = sieveOfEratosthenes(n);

    std::cout << "Prime numbers up to " << n << " are: ";
    for (int prime : primes)
        std::cout << prime << " ";

    std::cout << std::endl << std::endl << std::endl << "Fibonacci method:" << std::endl;

    std::cout << "Enter the number of Fibonacci numbers to generate: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Please enter a positive integer." << std::endl;
        return 1;
    }

    std::vector<long long> fib_sequence = fibonacci(n);

    std::cout << "The first " << n << " Fibonacci numbers are: ";
    for (long long number : fib_sequence) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    return 0;
}
std::vector<int> sieveOfEratosthenes(int n) {
    std::vector<int> primes;

    primes.push_back(1);

    for (int i = 2; i <= n; i++)
        if ((i == 2 || i == 3 || i == 5 || i == 7) || (i % 2 == 1 && i % 3 == 1 && i % 5 == 1 && i % 7 == 1))
            primes.push_back(i);

    return primes;
}

std::vector<long long> fibonacci(int n) {
    std::vector<long long> fib(n);
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i < n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib;
}