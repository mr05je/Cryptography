#include <string>

extern "C++" {
__declspec(dllexport) std::string Encrypt(const char* msg, const char* key) {
    std::string res = "1";
    return res;
}

__declspec(dllexport) std::string Decrypt(const char* msg, const char* key) {
    std::string res2 = "2";
    return res2;
}
};
