#include <map>
#include <iostream>
#include <sstream>

std::map<std::string, char> morseCode = {
    {"•–", 'А'}, {"–•••", 'Б'}, {"•––", 'В'}, {"––•", 'Г'},
    {"–••", 'Д'}, {"•", 'Е'}, {"•••–", 'Ж'}, {"––••", 'З'},
    {"••", 'И'}, {"•–––", 'Й'}, {"–•–", 'К'}, {"•–••", 'Л'},
    {"––", 'М'}, {"–•", 'Н'}, {"–––", 'О'}, {"•––•", 'П'},
    {"•–•", 'Р'}, {"•••", 'С'}, {"–", 'Т'}, {"••–", 'У'},
    {"••••", 'Х'}, {"––•–", 'Ц'}, {"–––•", 'Ч'}, {"––––", 'Ш'},
    {"––•–", 'Щ'}, {"–•––", 'Ъ'}, {"–•––", 'Ы'}, {"–••–", 'Ь'},
    {"••––••", 'Э'}, {"••––", 'Ю'}, {"•–•–", 'Я'}
};

std::string encodeMorse(const std::string &text);
std::string decodeMorse(const std::string &morse);

int main() {
    std::string word1 = "информатика", word2 = "данные", word3 ="алгоритм";
    std::string name1 = "Кован Николай", name2 = "Верстунин Павел", name3 = "Осадчий Илья";
    return 0;
}

std::string encodeMorse(const std::string &text) {
    std::string encoded;

    for (char c : text) {
        if (morseCode.find(c) != morseCode.end()) {
            encoded += morseCode[c] + " ";
        }
    }

    return encoded;
}

std::string decodeMorse(const std::string &morse) {
    std::stringstream ss(morse);
    std::string token;
    std::string decoded;

    while (std::getline(ss, token, ' ')) {
        if (morseCode.find(token) != morseCode.end()) {
            decoded += morseCode[token];
        } else {
            decoded += ' ';
        }
    }

    return decoded;
}