#include <locale>
#include <iostream>
#include <io.h>
#include <fcntl.h>

const wchar_t SubstitutionTable[2][118] = {
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', L'А', L'Б', L'В', L'Г', L'Д', L'Е', L'Ё', L'Ж', L'З', L'И', L'Й', L'К', L'Л', L'М', L'Н', L'О', L'П', L'Р', L'С', L'Т', L'У', L'Ф', L'Х', L'Ц', L'Ч', L'Ш', L'Щ', L'Ъ', L'Ы', L'Ь', L'Э', L'Ю', L'Я'},
        {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', L'Я', L'Ю', L'Э', L'Ь', L'Ы', L'Ъ', L'Щ', L'Ш', L'Ч', L'Ц', L'Х', L'Ф', L'У', L'Т', L'С', L'Р', L'П', L'О', L'Н', L'М', L'Л', L'К', L'Й', L'И', L'З', L'Ж', L'Ё', L'Е', L'Д', L'Г', L'В', L'Б', L'А'} // Substitute characters
};

wchar_t encryptChar(wchar_t ch);
wchar_t decryptChar(wchar_t ch);
std::wstring encrypt(const std::wstring &text);
std::wstring decrypt(const std::wstring &text);

int main() {
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin),  _O_U8TEXT);
    _setmode(_fileno(stderr), _O_U8TEXT);

    std::wstring text = L"Hello World Привет Мир";
    std::wstring encrypted = encrypt(text);
    std::wstring decrypted = decrypt(encrypted);

    std::wcout << "Original text: " << text << std::endl;
    std::wcout << "Encrypted text: " << encrypted << std::endl;
    std::wcout << "Decrypted text: " << decrypted << std::endl;

    return 0;
}

wchar_t encryptChar(wchar_t ch) {
    if (ch == ' ') return L'_';

    for (int i = 0; i < 118; ++i) {
        if (SubstitutionTable[0][i] == ch) {
            return SubstitutionTable[1][i];
        }
    }

    return ch;
}

wchar_t decryptChar(wchar_t ch) {
    if (ch == L'_') return L' ';

    for (int i = 0; i < 118; ++i) {
        if (SubstitutionTable[1][i] == ch) {
            return SubstitutionTable[0][i];
        }
    }

    return ch;
}

std::wstring encrypt(const std::wstring &text) {
    std::wstring encrypted;
    for (wchar_t ch : text) {
        encrypted += encryptChar(ch);
    }
    return encrypted;
}

std::wstring decrypt(const std::wstring &text) {
    std::wstring decrypted;
    for (wchar_t ch : text) {
        decrypted += decryptChar(ch);
    }
    return decrypted;
}