#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>
#include <io.h>

std::wstring fixedPeriodPermutation(const std::wstring &text, int period, const std::wstring &key);
std::wstring tableBasedPermutation(const std::wstring &text, int rows, int cols, const std::wstring &key);

int main() {
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin),  _O_U8TEXT);
    _setmode(_fileno(stderr), _O_U8TEXT);

    std::wstring text, key;
    std::wcout << L"Insert text: ";
    std::getline(std::wcin, text);
    std::wcout << L"Insert key: ";
    std::getline(std::wcin, key);
    std::wstring encryptedText = fixedPeriodPermutation(text, 6, key);
    std::wcout << L"Encrypted Text: " << encryptedText << std::endl;

    int rows = 3, cols = 4;
    encryptedText = tableBasedPermutation(text, rows, cols, key);
    std::wcout << "Encrypted Text: " << encryptedText << std::endl;

    return 0;
}

std::wstring fixedPeriodPermutation(const std::wstring &text, const int period, const std::wstring &key) {
    std::wstring encrypted = text;
    int blockSize = key.length();

    for (size_t i = 0; i < text.length(); i += blockSize) {
        for (size_t j = 0; j < blockSize; j++) {
            if (i + j < text.length()) {
                size_t keyIndex = key[j] - L'1';
                if (i + keyIndex < text.length()) {
                    encrypted[i + j] = text[i + keyIndex];
                }
            }
        }
    }

    return encrypted;
}

std::wstring tableBasedPermutation(const std::wstring &text, int rows, int cols, const std::wstring &key) {
    std::wstring encrypted = text;
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(cols, 0));

    size_t index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols && index < text.length(); j++) {
            table[i][j] = text[index++];
        }
    }

    index = 0;
    for (wchar_t ch : key) {
        int col = ch - L'1';
        for (int i = 0; i < rows; i++) {
            if (table[i][col] != 0) {
                encrypted[index++] = table[i][col];
            }
        }
    }

    return encrypted;
}