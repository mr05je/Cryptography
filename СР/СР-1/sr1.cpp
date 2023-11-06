#include <iostream>
#include <string>

std::string encrypt(const std::string& text, int n) {
    std::string encrypted_text = "";
    for (char character : text) {
        if (std::isalpha(character)) {
            int shift = (std::isupper(character)) ? 65 : 97;
            char encrypted_char = static_cast<char>((static_cast<int>(character) - shift + n) % 26 + shift);
            encrypted_text += encrypted_char;
        } else {
            encrypted_text += character;
        }
    }
    return encrypted_text;
}

std::string decrypt(const std::string& encrypted_text, int n) {
    std::string decrypted_text = "";
    for (char character : encrypted_text) {
        if (std::isalpha(character)) {
            int shift = (std::isupper(character)) ? 65 : 97;
            char decrypted_char = static_cast<char>((static_cast<int>(character) - shift - n + 26) % 26 + shift);
            decrypted_text += decrypted_char;
        } else {
            decrypted_text += character;
        }
    }
    return decrypted_text;
}

int main() {
    std::string name;
    int key;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    std::cout << "Enter the key (an integer from 1 to 32): ";
    std::cin >> key;

    std::string encrypted_name = encrypt(name, key);
    std::cout << "Encrypted Name: " << encrypted_name << std::endl;

    std::string decrypted_name = decrypt(encrypted_name, key);
    std::cout << "Decrypted Name: " << decrypted_name << std::endl;

    return 0;
}
