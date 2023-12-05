#include <iostream>
#include <string>
#include <map>
#include <vector>

std::map<char, std::pair<int, int>> codingTable = {
    {'А', {0, 0}}, {'Б', {0, 1}}, {'В', {0, 2}}, {'Г', {0, 3}},
    {'Д', {0, 4}}, {'Е', {0, 5}}, {'Ж', {0, 6}}, {'З', {0, 7}},
    {'И', {0, 8}},
    {'Й', {1, 0}}, {'К', {1, 1}}, {'Л', {1, 2}}, {'М', {1, 3}},
    {'Н', {1, 4}}, {'О', {1, 5}}, {'П', {1, 6}}, {'Р', {1, 7}},
    {'С', {1, 8}},
    {'Т', {2, 0}}, {'У', {2, 1}}, {'Ф', {2, 2}}, {'Х', {2, 3}},
    {'Ц', {2, 4}}, {'Ч', {2, 5}}, {'Ш', {2, 6}}, {'Щ', {2, 7}},
    {'Ъ', {2, 8}},
    {'Ы', {3, 0}}, {'Ь', {3, 1}}, {'Э', {3, 2}}, {'Ю', {3, 3}},
    {'Я', {3, 4}}, {'_', {3, 5}}, {'.', {3, 6}}, {',', {3, 7}},
    {'?', {3, 8}},
    {':', {4, 0}}, {';', {4, 1}}, {'-', {4, 2}}, {'!', {4, 3}},
    {'"', {4, 4}}
};

std::map<std::pair<int, int>, char> reverseCodingTable = {
    {{0, 0}, 'А'}, {{0, 1}, 'Б'}, {{0, 2}, 'В'}, {{0, 3}, 'Г'},
    {{0, 4}, 'Д'}, {{0, 5}, 'Е'}, {{0, 6}, 'Ж'}, {{0, 7}, 'З'},
    {{0, 8}, 'И'}, {{1, 0}, 'Й'}, {{1, 1}, 'К'}, {{1, 2}, 'Л'},
    {{1, 3}, 'М'}, {{1, 4}, 'Н'}, {{1, 5}, 'О'}, {{1, 6}, 'П'},
    {{1, 7}, 'Р'}, {{1, 8}, 'С'}, {{2, 0}, 'Т'}, {{2, 1}, 'У'},
    {{2, 2}, 'Ф'}, {{2, 3}, 'Х'}, {{2, 4}, 'Ц'}, {{2, 5}, 'Ч'},
    {{2, 6}, 'Ш'}, {{2, 7}, 'Щ'}, {{2, 8}, 'Ъ'}, {{3, 0}, 'Ы'},
    {{3, 1}, 'Ь'}, {{3, 2}, 'Э'}, {{3, 3}, 'Ю'}, {{3, 4}, 'Я'},
    {{3, 5}, '_'}, {{3, 6}, '.'}, {{3, 7}, ','}, {{3, 8}, '?'},
    {{4, 0}, ':'}, {{4, 1}, ';'}, {{4, 2}, '-'}, {{4, 3}, '!'},
    {{4, 4}, '"'}
};

std::string encodeText(const std::string &text);
std::string decodeText(const std::string &encodedText);

int main() {
    std::string textToEncode = "Я УМЕЮ РАБОТАТЬ";
    std::string encodedText = encodeText(textToEncode);

    std::cout << "Encoded Text: " << encodedText << std::endl;
    
    std::string decodedText = decodeText(encodedText);
    std::cout << "Decoded Text: " << decodedText << std::endl;

    return 0;
}

std::string encodeText(const std::string &text) {
    std::string encodedText;
    for (char c : text) {
        if (codingTable.find(c) != codingTable.end()) {
            encodedText += std::to_string(codingTable[c].first) + std::to_string(codingTable[c].second) + "_";
        } else {
            encodedText += "?? ";
        }
    }
    return encodedText;
}

std::string decodeText(const std::string &encodedText) {
    std::string decodedText;
    std::vector<std::string> encodedSymbols;
    std::string currentSymbol;

    for (char c : encodedText) {
        if (c == ' ') {
            if (!currentSymbol.empty()) {
                encodedSymbols.push_back(currentSymbol);
                currentSymbol.clear();
            }
        } else {
            currentSymbol += c;
        }
    }
    if (!currentSymbol.empty()) {
        encodedSymbols.push_back(currentSymbol);
    }

    for (const std::string &symbol : encodedSymbols) {
        if (symbol == "_") {
            decodedText += ' ';
            continue;
        }

        int row = symbol[0] - '0';
        int column = symbol[1] - '0';

        auto it = reverseCodingTable.find({row, column});
        if (it != reverseCodingTable.end()) {
            decodedText += it->second;
        } else {
            decodedText += '?'; 
        }
    }

    return decodedText;
}