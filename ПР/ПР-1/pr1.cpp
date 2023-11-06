#include <iostream>
#include <tuple>

#define cout(text) std::cout << text << std::endl
#define coutd(text, data) std::cout << text << " = " << data << std::endl
#define cexit(text) {cout(text); return 0;}

bool USE_VARIANTS = true;

int GCD(int a, int b);
std::tuple<int, int, int> GCDExtended(int a, int b);
std::tuple<int, int> DE(int a, int b, int c);

int main(int argc, [[maybe_unused]] char** argv) {
    if (argc > 1)
    {
        USE_VARIANTS = true;
    }
    int a, b;
    cout("Insert numbers a and b (example: \"24 2\")");
    std::cin >> a >> b;
    std::cout << "GCD of numbers " << a << " and " << b << " = ";
    cout(GCD(a, b));

    int n, a1, b1, c1;
    if (USE_VARIANTS) {
        cout("Insert your variant number");
        std::cin >> n;

        a1 = (n + 1) * (n + 2);
        b1 = (n + 2) * (n + 3);
        c1 = (n + 2) * (n + 2) * (n + 2);
    }
    else {
        cout("Insert a, b and c numbers (example: \"5 6 7\")");
        std::cin >> a1 >> b1 >> c1;
    }

    auto de = DE(a1, b1, c1);
    int x = std::get<0>(de);
    int y = std::get<1>(de);

    if (x == 0 && y == 0) {
        cout("There are no roots!");
        cout("Calculating for 8x + 16y = 64 ...");

        a1 = 8; b1 = 16, c1 = 64;

        de = DE(a1, b1, c1);
        x = std::get<0>(de);
        y = std::get<1>(de);

        if (x == 0 && y == 0) {
            cexit("There are no roots!")
        }
        coutd("x", x);
        coutd("y", y);
    } else {
        coutd("x", x);
        coutd("y", y);
    }

    return 0;
}

int GCD(int a, int b) {
    return b == 0 ? a : GCD(b, a % b);
}

std::tuple<int, int, int> GCDExtended(int a, int b) {
    if (b == 0) {
        return std::make_tuple(a, 1, 0);
    } else {
        int gcd, x1, y1;
        std::tie(gcd, x1, y1) = GCDExtended(b, a % b);
        int x = y1;
        int y = x1 - (a / b) * y1;
        return std::make_tuple(gcd, x, y);
    }
}

std::tuple<int, int> DE(int a, int b, int c) {
    int g = GCD(a, b);

    if (c % g != 0) // check if c divides GCD(a, b)
        return std::make_tuple(0, 0);

    a /= g;
    b /= g;
    c /= g;

    auto gcd_extended = GCDExtended(a, b);

    int gcd = std::get<0>(gcd_extended);
    int x = std::get<1>(gcd_extended);
    int y = std::get<2>(gcd_extended);

    if (gcd != 1) {
        // If the GCD of a and b is not 1, then there's no solution
        return std::make_tuple(0, 0);
    }

    x *= c;
    y *= c;

    return std::make_tuple(x, y);
}