#include <iostream>
#include <string>
#include <utility>
#include <limits>
#include <io.h>
#include <fcntl.h>

int lcg(int seed, int a, int c, int m);
int prng(int seed, int a, int c, int m);
std::wstring streamCipher(std::wstring text, int seed, int a, int c, int m);

int main() {
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin),  _O_U8TEXT);
    _setmode(_fileno(stderr), _O_U8TEXT);

    std::wstring text;
    int seed, n, a = 1103515245, c = 12345, m = 1 << 31;

    std::wcout << "Stream Cipher Simulation" << std::endl;
    std::wcout << "Insert seed (as number):";
    std::wcin >> seed;
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::wcout << "Enter a string to encrypt/decrypt:";

    std::getline(std::wcin, text);

    std::wstring encrypted = streamCipher(text, seed, a, c, m);
    std::wstring decrypted = streamCipher(encrypted, seed, a, c, m);

    std::wcout << "Encrypted: " << encrypted << "\n";
    std::wcout << "Decrypted: " << decrypted << "\n";

    std::wcout << std::endl << "Random numbers" << std::endl;

    std::wcout << "Insert n:" ;

    std::wcin >> n;

    for (int i = 0; i < n; i++) {
        seed = lcg(seed, a, c, m);
        std::wcout << "Random number " << i + 1 << ": " << seed << std::endl;
    }

    return 0;
}

int lcg(int seed, int a, int c, int m) {
    return (a * seed + c) % m;
}

int prng(int seed, int a, int c, int m) {
    return (a * seed + c) % m;
}

std::wstring streamCipher(std::wstring text, int seed, int a, int c, int m) {
    std::wstring result = std::move(text);

    for (wchar_t &ch : result) {
        seed = prng(seed, a, c, m);
        ch ^= seed;
    }

    return result;
}