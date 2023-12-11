#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

#pragma region utils
#define ll long long

int GCD(int a, int b);
#pragma endregion

#pragma region euler phi
int eulerPhi(int n);
#pragma endregion

#pragma region pollards rho
ll mulmod(ll a, ll b, ll mod);
ll pollards_rho(ll n);
#pragma endregion

#pragma region fermat factorization
bool isPerfectSquare(long long n);
void fermatFactorization(long long n);
#pragma endregion

int main() {
    int n;
    std::cout << "Insert number: ";
    std::cin >> n;
    std::cout << "Euler's Totient Function for " << n << " is " << eulerPhi(n) << std::endl;

    std::cout << std::endl;

    srand(time(NULL));
    ll number = 13;
    std::cout << "A nontrivial factor of " << number << " is " << pollards_rho(number) << std::endl;

    std::cout << std::endl;

    std::cout << "Fermat's Factorization of " << number << ":" << std::endl;
    fermatFactorization(number);

    return 0;
}

int GCD(int a, int b) {
    return b == 0 ? a : GCD(b, a % b);
}

int eulerPhi(int n) {
    int result = n;

    for(int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }

    if (n > 1)
        result -= result / n;

    return result;
}

ll mulmod(ll a, ll b, ll mod) {
    ll result = 0;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return result % mod;
}

ll pollards_rho(ll n) {
    if (n % 2 == 0)
        return 2;

    ll x = 2;
    ll y = 2;
    ll d = 1;
    ll c = rand() % n + 1;

    while (d == 1) {
        x = (mulmod(x, x, n) + c + n) % n;
        y = (mulmod(y, y, n) + c + n) % n;
        y = (mulmod(y, y, n) + c + n) % n;
        d = GCD(std::abs(x - y), n);
    }

    return d;
}

bool isPerfectSquare(long long n) {
    long long sqrt_n = std::sqrt(n);
    return (sqrt_n * sqrt_n == n);
}

void fermatFactorization(long long n) {
    if (n % 2 == 0) {
        std::cout << n << " is an even number." << std::endl;
        return;
    }

    long long a = std::ceil(std::sqrt(n));
    long long b2 = a * a - n;

    while (!isPerfectSquare(b2)) {
        a++;
        b2 = a * a - n;
    }

    long long r1 = a + std::sqrt(b2);
    long long r2 = a - std::sqrt(b2);

    std::cout << n << " = " << r1 << " * " << r2 << std::endl;
}