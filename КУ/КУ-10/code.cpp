#include <iostream>
#include <string>
#include <algorithm>

std::string decimalToBinary(int number);
int binaryToDecimal(const std::string &binary);
std::string xorOperation(const std::string &text, const std::string &key);

int main() {
    int originalNumber, keyNumber;
    std::cout << "Insert original number: ";
    std::cin >> originalNumber;
    std::cout << "Insert key: ";
    std::cin >> keyNumber;

    std::string originalBinary = decimalToBinary(originalNumber);
    std::string keyBinary = decimalToBinary(keyNumber);

    while (originalBinary.length() < keyBinary.length()) originalBinary.insert(0, "0");
    while (keyBinary.length() < originalBinary.length()) keyBinary.insert(0, "0");

    std::string encryptedBinary = xorOperation(originalBinary, keyBinary);
    int encryptedNumber = binaryToDecimal(encryptedBinary);

    std::string decryptedBinary = xorOperation(encryptedBinary, keyBinary);
    int decryptedNumber = binaryToDecimal(decryptedBinary);

    std::cout << "Original Number: " << originalNumber << " (Binary: " << originalBinary << ")" << std::endl;
    std::cout << "Key: " << keyNumber << " (Binary: " << keyBinary << ")" << std::endl;
    std::cout << "Encrypted Number: " << encryptedNumber << " (Binary: " << encryptedBinary << ")" << std::endl;
    std::cout << "Decrypted Number: " << decryptedNumber << " (Binary: " << decryptedBinary << ")" << std::endl;

    return 0;
}

std::string decimalToBinary(int number) {
    std::string binary;
    while (number > 0) {
        binary += (number % 2 == 0 ? "0" : "1");
        number /= 2;
    }

    std::reverse(binary.begin(), binary.end());
    return binary;
}

int binaryToDecimal(const std::string &binary) {
    int number = 0;
    int base = 1;
    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            number += base;
        }
        base *= 2;
    }
    return number;
}

std::string xorOperation(const std::string &text, const std::string &key) {
    std::string result;
    for (size_t i = 0; i < text.length(); ++i) {
        result += (text[i] == key[i] ? '0' : '1');
    }
    return result;
}