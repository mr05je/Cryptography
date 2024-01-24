#include <wchar.h>
#include <string>
#include <utility>
#include <vector>
#include <stdint.h>
#include <array>
#include <tuple>
#include <codecvt>
#include <unordered_map>

#include "base64.h"

#ifndef CRYPTOGRAPHY_FIESTELNETWORK_H
#define CRYPTOGRAPHY_FIESTELNETWORK_H

class FiestelNetwork {
public:
    FiestelNetwork(std::wstring input, std::wstring key) : _input(std::move(input)), _key(std::move(key)) {init();};
private:
    std::wstring _key, _input;
    std::array<uint8_t, 7> _key_52b{};
    std::vector<std::array<uint8_t, 8>> _input_64b_blocks;

    void init();
    // 48 bits
    std::array<uint8_t, 6> gen_key(int round);
    std::array<uint8_t, 6> extend(std::array<uint8_t, 4> byte_block);
    std::array<uint8_t, 4> compress(std::array<uint8_t, 6> byte_block);
    std::pair<std::array<uint8_t, 4>, std::array<uint8_t, 4>> round(int round, std::array<uint8_t, 4> l, std::array<uint8_t, 4> r);

    const uint8_t _KT[48] = {
            0x73,0x63, 0x75, 0x33, 0x70, 0x56, 0x65, 0x72,
            0x5f,0x73, 0x74, 0x72, 0x6f, 0x6e, 0x67, 0x5f,
            0x34,0x38, 0x62, 0x69, 0x74, 0x5f, 0x74, 0x61,
            0x62,0x6c, 0x65, 0x58,0x33,0x52,0x68,0x59,
            0x6d,0x78,0x6c, 0x4a,0x66,0x63,0x33,0x52,
            0x79,0x62,0x32,0x30,0x58,0x33,0x52,0x30,
    };

    const uint8_t _ST[48] = {
            0x63, 0x33, 0x56, 0x77, 0x5a, 0x58, 0x49, 0x74,
            0x63, 0x33, 0x52, 0x79, 0x62, 0x32, 0x35, 0x6e,
            0x4c, 0x58, 0x4a, 0x76, 0x64, 0x47, 0x39, 0x79,
            0x4c, 0x58, 0x4e, 0x69, 0x62, 0x47, 0x39, 0x6a,
            0x61, 0x33, 0x52, 0x68, 0x59, 0x6d, 0x78, 0x6c,
            0x5a, 0x6e, 0x4a, 0x6c, 0x5a, 0x56, 0x39, 0x6a
    };

    const int _PI[32] = {
            25, 16, 14, 5, 6, 20, 31, 18,
            3, 4, 24, 12, 22, 30, 1, 13,
            8, 9, 17, 15, 28, 26, 27, 11,
            29, 0, 7, 19, 21, 23, 2, 10
    };
};

#endif //CRYPTOGRAPHY_FIESTELNETWORK_H
