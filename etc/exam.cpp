#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <io.h>
#include <fcntl.h>
#include <limits>

std::map<wchar_t, std::wstring> CodeTable = {{L' ', L"_"}};

std::wstring semanticEncode(const std::wstring &text);

int main() {
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin),  _O_U8TEXT);
    _setmode(_fileno(stderr), _O_U8TEXT);

    std::wstring text, code, t;

    std::wcout << L"Insert text: ";
    std::getline(std::wcin, text);

    std::wistringstream wiss(text);

    while (std::getline(wiss, t, L' ')) {
        for (wchar_t ch : t) {
            if (CodeTable.count(ch) == 0) {
                std::wcout << L"Insert code for symbol '" << ch << L"': ";
                std::getline(std::wcin, code);
                CodeTable.insert({ch, code});
            }
        }
    }

    std::wcout << L"Encrypted text: " << semanticEncode(text) << std::endl;

    std::cin;
    return 0;
}

std::wstring semanticEncode(const std::wstring &text) {
    std::wstring res;
    for (wchar_t ch : text) {
        if (CodeTable.count(ch) == 1) {
            res += CodeTable[ch];
        }
    }

    return res;
}