#include <iostream>
#include <vector>
#include <string>

std::vector<char> xorEncryptDecrypt(const std::string &text, char key);

int main() {
    std::string text;
    char key;

    std::cout << "Enter text: ";
    getline(std::cin, text);

    std::cout << "Enter key (one character): ";
    std::cin >> key;

    std::vector<char> encrypted = xorEncryptDecrypt(text, key);
    std::vector<char> decrypted = xorEncryptDecrypt(std::string(encrypted.begin(), encrypted.end()), key);

    std::cout << "Encrypted: ";
    for (char c : encrypted) {
        std::cout << c;
    }
    std::cout << std::endl;

    std::cout << "Decrypted: ";
    for (char c : decrypted) {
        std::cout << c;
    }
    std::cout << std::endl;

    return 0;
}

std::vector<char> xorEncryptDecrypt(const std::string &text, char key) {
    std::vector<char> result;
    for (char c : text) {
        result.push_back(c ^ key);
    }
    return result;
}