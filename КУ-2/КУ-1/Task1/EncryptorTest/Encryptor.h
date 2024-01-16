#pragma once

#ifdef ENCRYPTOR_EXPORTS
#define ENCRYPTOR_API __declspec(dllexport)
#else
#define ENCRYPTOR_API __declspec(dllexport)
#endif
#include <string>
#include <vector>

extern "C" {

    ENCRYPTOR_API const wchar_t* encrypt(const wchar_t* msg, const wchar_t* key);
    ENCRYPTOR_API const wchar_t* decrypt(const wchar_t* msg, const wchar_t* key);
}

int get_key(const wchar_t* key);
std::vector<std::vector<wchar_t>> convert_wstring_to_table(const std::wstring& msg);
std::vector<std::vector<wchar_t>> shift_table(const int& key, const std::vector<std::vector<wchar_t>>& table);