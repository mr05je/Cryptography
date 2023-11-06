#include <iostream>
#include <random>
#include <math.h>
#include <chrono>

#define cout(text) std::cout << text << std::endl
#define coutd(text, data) std::cout << text << " = " << data << std::endl
#define coutt(test_name, data) std::cout << "Executing " << test_name << "(" << data << ")" << std::endl
#define couttt(test_name, data, time) std::cout << "Runtime of " << test_name << "(" << data << "): " << time << "ms (" << time/1000 << "s)" << std::endl
#define coutr(test_name, data, res, time) std::cout << "Result of " << test_name << "(" << data <<"): " << res << std::endl; couttt(test_name, data, time)
#define coutrnt(test_name, data, res) std::cout << "Result of " << test_name << "(" << data <<"): " << res << std::endl
#define td std::cout << "----------------------------------------------------------------------------------------------" << std::endl
#define rd std::cout << std::endl << "\033[32m" << "----------------------------------------------------------------------------------------------" << "\033[0m" << std::endl << std::endl
#define brd std::cout << std::endl << "\033[31m" << "----------------------------------------------------------------------------------------------" << "\033[0m" << std::endl << std::endl

#define cexit(text) {cout(text); return 0;}
#define ll long long

bool REQUIRE_BENCHMARK = false;

int BaseCheck(ll n);
int PowerMod(ll base, ll exponent, ll modulus);
bool IsPrimeByRoot(ll n);
bool IsPrimeByMillerRabinTest(ll n, ll k);
bool IsPrimeByFerma(ll n, ll k);
bool IsPrimeBySieveEratosthenes(ll n);
void ExecuteTests(ll n1, ll n2, ll n3, ll n4, ll n5, ll k);
void ExecuteTest(ll n, ll k);

int main(int argc) {
    if (argc >= 2) REQUIRE_BENCHMARK = true;
    ll n1_1, n1_2, n1_3, //5
       n2_1, n2_2, n2_3, //13
       n3_1, n3_2, n3_3, //22
       n5_1, n5_2, n5_3, n4, k;

    n1_1 = std::pow(33-5, 2) + 1 ;
    n1_2 = std::pow(5+1, 2) - 1;
    n1_3 = std::pow(2, std::pow(2, 5 % 4)) + 1;

    n2_1 = std::pow(33-13, 2) + 1 ;
    n2_2 = std::pow(13+1, 2) - 1;
    n2_3 = std::pow(2, std::pow(2, 13 % 4)) + 1;

    n3_1 = std::pow(33-22, 2) + 1 ;
    n3_2 = std::pow(22+1, 2) - 1;
    n3_3 = std::pow(2, std::pow(2, 22 % 4)) + 1;

    n5_1 = 20050906;
    n5_2 = 20050719;
    n5_3 = 20050606;

    n4 = 20231107;

    cout("Insert number of iterations for Ferma and Miller-Rabin test");
    std::cin >> k;

    ExecuteTests(n1_1, n2_1, n3_1, n4, n5_1, k);
    brd;
    ExecuteTests(n1_2, n2_2, n3_2, 0, n5_2, k);
    brd;
    ExecuteTests(n1_3, n2_3, n3_3, 0, n5_3, k);

    int t1, t2, t3, t4, t5, kk;

    cout("Insert 5 number for tests");
    std::cin >> t1 >> t2 >> t3 >> t4 >> t5;

    cout("Insert number of iterations for Ferma and Miller-Rabin test");
    std::cin >> kk;

    brd;
    ExecuteTests(t1, t2, t3, t4, t5, kk);
    return 0;
}

int BaseCheck(ll n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    return 2;
}

bool IsPrimeByRoot(ll n) {
    if (auto check = BaseCheck(n); check != 2) return (bool)check;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;

    return true;
}

bool IsPrimeByMillerRabinTest(ll n, ll k) {
    if (auto check = BaseCheck(n); check != 2) return (bool)check;

    ll r = 0;
    ll d = n - 1;

    while (d % 2 == 0) {
        r++;
        d /= 2;
    }

    std::random_device dev;
    std::mt19937 rng(dev());

    for (int i = 0; i < k; i++) {
        int a = 2 + std::uniform_int_distribution<std::mt19937::result_type>(2,n - 2)(rng);
        int x = (ll) std::pow(a, d) % n;

        if (x == 1 || x == n - 1) continue;

        for (int j = 0; j < r - 1; j++)
            if (x = (ll) std::pow(x, 2) % n; x == n - 1) break;

        if (x != n - 1) return false;
    }

    return true;
}

bool IsPrimeByFerma(ll n, ll k) {
    if (n <= 1 || n % 2 == 0) {
        return n == 2;
    }

    std::random_device dev;
    std::mt19937 rng(dev());

    for (int i = 0; i < k; i++)
        if (PowerMod(
                std::uniform_int_distribution<std::mt19937::result_type>(2,n - 2)(rng) + 2,
                        n - 1,n) != 1)
            return false;

    return true;
}

bool IsPrimeBySieveEratosthenes(ll n) {
    bool* isPrime = new bool[n + 1];

    for (int i = 2; i <= n; i++)
        isPrime[i] = true;

    for (int p = 2; p * p <= n; p++)
        if (isPrime[p])
            for (int i = p * p; i <= n; i += p)
                isPrime[i] = false;

    return isPrime[n];
}

int PowerMod(ll base, ll exponent, ll modulus) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

void ExecuteTests(ll n1 ,ll n2, ll n3, ll n4, ll n5, ll k) {
    ExecuteTest(n1, k);
    rd;
    ExecuteTest(n2, k);
    rd;
    ExecuteTest(n3, k);
    rd;
    if (n4 != 0) {ExecuteTest(n4, k); rd;}
    ExecuteTest(n5, k);
}

void ExecuteTest(ll n, ll k) {
    coutt("IsPrimeByRoot", n);
    auto start = std::chrono::system_clock::now();
    auto result = IsPrimeByRoot(n);
    auto end = std::chrono::system_clock::now();
    if (REQUIRE_BENCHMARK) { coutr("IsPrimeByRoot", n, result, std::chrono::duration_cast<std::chrono::milliseconds>(start - end).count()); }
    else coutrnt("IsPrimeByRoot", n, result);

    td;
    coutt("IsPrimeByMillerRabinTest", n);
    start = std::chrono::system_clock::now();
    result = IsPrimeByMillerRabinTest(n, k);
    end = std::chrono::system_clock::now();
    if (REQUIRE_BENCHMARK) { coutr("IsPrimeByMillerRabinTest", n, result, std::chrono::duration_cast<std::chrono::milliseconds>(start - end).count()); }
    else coutrnt("IsPrimeByMillerRabinTest", n, result);

    td;
    coutt("IsPrimeByFerma", n);
    start = std::chrono::system_clock::now();
    result = IsPrimeByFerma(n, k);
    end = std::chrono::system_clock::now();
    if (REQUIRE_BENCHMARK) { coutr("IsPrimeByFerma", n, result, std::chrono::duration_cast<std::chrono::milliseconds>(start - end).count()); }
    else coutrnt("IsPrimeByFerma", n, result);

    td;
    coutt("IsPrimeBySieveEratosthenes", n);
    start = std::chrono::system_clock::now();
    result = IsPrimeBySieveEratosthenes(n);
    end = std::chrono::system_clock::now();
    if (REQUIRE_BENCHMARK) { coutr("IsPrimeBySieveEratosthenes", n, result,
              std::chrono::duration_cast<std::chrono::milliseconds>(start - end).count()); }
    else coutrnt("IsPrimeBySieveEratosthenes", n, result);
}