#include "FiestelNetwork.h"

void FiestelNetwork::init() {
    std::vector<uint8_t> input_bits(this->_input.begin(), this->_input.end());

    std::array<uint8_t, 8> temp{};
    int t_i = 0;
    for (int i = 0; i < input_bits.size(); ++i) {
        if (i % 8 == 0 && i != 0) {
            this->_input_64b_blocks.push_back(temp);
            temp = {};
            t_i = 0;
        } else {
            temp[t_i] = input_bits[i];
            t_i++;
        }
    }

    if (t_i != 0) {
        for (int i = 0; i < 8-t_i; i++) {
            temp[8-i] = 0x00;
        }
    }

    std::string base64_k = Base64().Encode(this->_key);
    std::string base64_sub_k;

    std::array<uint8_t, 7> sub_k_b = {};

    if (base64_k.length() > 8) {
        int middle = base64_k.length()/2;
        base64_sub_k = std::string(base64_k.begin() + middle - 4, base64_k.end() - middle + 4);
    } else {
        while (base64_k.length() < 8) {
            base64_k += "=";
            base64_sub_k = std::string(base64_k);
        }
    }

    uint8_t temp_b = 0x00, temp_c_b;
    char temp_c = '\000';
    int i = 0;

    for (const auto c : base64_sub_k) {
        if (temp_c != '\000')
            temp_b <<= 7;
        temp_c_b = static_cast<uint8_t>(c) & 0x7F;
        temp_b |= temp_c_b;

        if (temp_c != '\000')
        {
            sub_k_b[i] = temp_b;
            i++;
        }
        temp_c = c;
    }

    this->_key_52b = sub_k_b;
}

std::array<uint8_t, 6> FiestelNetwork::gen_key(int round) {
    uint8_t left[4], right[4];
    uint32_t left26bits = 0, right26bits = 0;

    left26bits |= static_cast<uint32_t>(this->_key_52b[0]) << 18;
    left26bits |= static_cast<uint32_t>(this->_key_52b[1]) << 10;
    left26bits |= static_cast<uint32_t>(this->_key_52b[2]) << 2;
    left26bits |= static_cast<uint32_t>(this->_key_52b[3]) >> 6;
    right26bits |= (static_cast<uint32_t>(this->_key_52b[3]) & 0x3F) << 20;
    right26bits |= static_cast<uint32_t>(this->_key_52b[4]) << 12;
    right26bits |= static_cast<uint32_t>(this->_key_52b[5]) << 4;
    right26bits |= static_cast<uint32_t>(this->_key_52b[6]) >> 4;

    left[0] = static_cast<uint8_t>((left26bits >> 24) & 0xFF);
    left[1] = static_cast<uint8_t>((left26bits >> 16) & 0xFF);
    left[2] = static_cast<uint8_t>((left26bits >> 8) & 0xFF);
    left[3] = static_cast<uint8_t>(left26bits& 0xFF);

    right[0] = static_cast<uint8_t>((right26bits >> 24) & 0xFF);
    right[1] = static_cast<uint8_t>((right26bits >> 16) & 0xFF);
    right[2] = static_cast<uint8_t>((right26bits >> 8) & 0xFF);
    right[3] = static_cast<uint8_t>(right26bits & 0xFF);

    return std::array<uint8_t , 6> {};
}