#include <iostream>
#include <string>

std::string caesarEncrypt(const std::string &text, int shift);
std::string caesarDecrypt(const std::string &text, int sgift); 

int main() {
    std::string text;
    int shift;

    std::cout << "Enter text: ";
    getline(std::cin, text);

    std::cout << "Enter shift: ";
    std::cin >> shift;

    std::string encrypted = caesarEncrypt(text, shift);
    std::string decrypted = caesarDecrypt(encrypted, shift);

    std::cout << "Encrypted: " << encrypted << std::endl;
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}

std::string caesarEncrypt(const std::string &text, int shift) {
    std::string result = "";

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            result += static_cast<char>(base + (text[i] - base + shift) % 26);
        } else {
            result += text[i];
        }
    }

    return result;
}

std::string caesarDecrypt(const std::string &text, int shift) {
    return caesarEncrypt(text, 26 - shift);
}