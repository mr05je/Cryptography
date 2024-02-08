#include <stdint.h>
#include <vector>
#include <tuple>

#ifndef CRYPTOGRAPHY_DES_H
#define CRYPTOGRAPHY_DES_H

#define get_bit(number, k, p) (((1 << k) - 1) & (number >> (p - 1)));


class DES {
private:
    uint64_t _56_key;
    std::vector<uint64_t> blocks;

    int _E16BB[32] = {
            0, 5, 3, 4, 3, 5, 3, 6,
            7, 6, 4, 0, 0, 0, 0, 4,
            0, 1, 5, 4, 3, 4, 1, 6,
            7, 4, 1, 1, 4, 4, 4, 7
    };

    int _SBI[48] = {
            5, 18, 30, 17, 10, 6, 15, 7,
            9, 44, 8, 25, 2, 12, 45, 1,
            4, 16, 29, 41, 3, 36, 34, 32,
            46, 27, 28, 40, 26, 11, 19, 13,
            31, 21, 35, 33, 0, 24, 38, 39,
            14, 23, 42, 37, 22, 43, 47, 20
    };

    int _PBI[32] = {
             
    };

    // 32 to 48
    uint64_t extend_to_48b(uint32_t block);

    // 48 to 32
    uint32_t compress_to_32b(uint64_t block);
    // 26 to 24
    uint32_t compress_to_24b(uint32_t block);

    uint64_t gen_round_key(int round);
    std::pair<uint32_t, uint32_t> round(uint32_t l_block, uint32_t r_block, uint64_t round_key);


    void init();

};


#endif //CRYPTOGRAPHY_DES_H
