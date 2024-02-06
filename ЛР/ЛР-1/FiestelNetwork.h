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
            0x73, 0x63, 0x75, 0x33, 0x70, 0x56, 0x65, 0x72,
            0x5f, 0x73, 0x74, 0x72, 0x6f, 0x6e, 0x67, 0x5f,
            0x34, 0x38, 0x62, 0x69, 0x74, 0x5f, 0x74, 0x61,
            0x62, 0x6c, 0x65, 0x58, 0x33,0x52, 0x68, 0x59,
            0x6d, 0x78, 0x6c, 0x4a, 0x66, 0x63, 0x33, 0x52,
            0x79, 0x62, 0x32, 0x30, 0x58, 0x33, 0x52, 0x30,
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

    const int _KPI[2][28] = {
            {
                    18, 17, 14, 28, 11, 16, 19, 10,
                    5, 15, 9, 25, 27, 6, 4, 0,
                    8, 20, 26, 13, 2, 22, 1, 21,
                    24, 7, 3, 23
            },
            {
                    16, 21, 19, 13, 23, 0, 18, 27,
                    7, 5, 3, 12, 4, 15, 17, 10,
                    20, 6, 14, 9, 1, 11, 8, 22,
                    25, 2, 26, 24
            }
    };

    const int _CI[2][4] = {
            {
                    22, 7, 6, 12
            },
            {
                    9, 26, 5, 24
            }
    };

    const std::pair<int, uint8_t> _EI[16] = {
            {0x1f, 24}, {0x0d, 3}, {0xda, 44}, {0xea, 10},
            {0xe2, 27}, {0x47, 41}, {0x68, 34}, {0x75, 18},
            {0x1f, 33}, {0xb3, 28}, {0x75, 42}, {0x2a, 5},
            {0x79, 39}, {0x28, 43}, {0xe4, 19}, {0x98, 20}
    };
};

#endif //CRYPTOGRAPHY_FIESTELNETWORK_H
