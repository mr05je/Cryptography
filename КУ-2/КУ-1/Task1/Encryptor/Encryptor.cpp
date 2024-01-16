#include "Encryptor.h"

#include <locale>
#include <wchar.h>
#include <string>
#include <vector>

#ifdef ENCRYPTOR_EXPORTS
#define ENCRYPTOR_API __declspec(dllexport)
#else
#define ENCRYPTOR_API __declspec(dllexport)
#endif

extern "C" {

    ENCRYPTOR_API const wchar_t* encrypt(const wchar_t* msg, const wchar_t* key)
    {
        std::wstring result = L"2";
        if (msg[0] == L'\0')
        {
            return _wcsdup(result.c_str());
        }
        result = L"";
        const std::vector<std::vector<wchar_t>> table;
        const auto normal_key = get_key(key);

        const auto tabled_wstring = convert_wstring_to_table(msg);
        const auto new_table = shift_table(normal_key, tabled_wstring);

        for (const auto& row : new_table)
            for (const auto col : row)
                result += col;
        
        return _wcsdup(result.c_str());
    }

    ENCRYPTOR_API const wchar_t* decrypt(const wchar_t* msg, const wchar_t* key)
    {
        std::wstring result = L"";

        const std::vector<std::vector<wchar_t>> table;
        const auto normal_key = get_key(key);

        const auto tabled_wstring = convert_wstring_to_table(msg);
        const auto new_table = shift_table(-normal_key, tabled_wstring);
        
        for (const auto& row : new_table)
            for (const auto col : row)
                result += col;  
        
        return _wcsdup(result.c_str());
    }
}

int get_key(const wchar_t* key)
{
    const auto normalized_key = std::wstring(key);

    int res = 0;

    for (const wchar_t c : normalized_key)
        res += static_cast<int>(c);
    
    return res;
}

std::vector<std::vector<wchar_t>> convert_wstring_to_table(const std::wstring& msg)
{
    const size_t len = msg.length();
    const size_t num_rows = static_cast<size_t>(sqrt(len));
    const size_t num_cols = static_cast<size_t>(ceil(static_cast<double>(len) / num_rows));

    std::vector<std::vector<wchar_t>> wchar_2d_array(num_rows, std::vector<wchar_t>(num_cols, L' '));

    size_t index = 0;
    for (size_t row = 0; row < num_rows; ++row) {
        for (size_t col = 0; col < num_cols && index < len; ++col) {
            wchar_2d_array[row][col] = msg[index++];
        }
    }

    return wchar_2d_array;
}


std::vector<std::vector<wchar_t>> shift_table(const int& key, const std::vector<std::vector<wchar_t>>& table)
{
    std::vector<std::vector<wchar_t>> res;
    
    std::copy(table.begin(), table.end(), std::back_inserter(res));

    int rows = 0;
    int cols = 0;

    for(const auto row : table)
        rows ++;

    for(const auto col : table[0])
        cols ++;
    

    
    for (int i = 0; i < rows; i++) // i - current row
    {
        for (int j = 0; j < cols; j++) //j - current col
        {
            int new_row = 0;
            int new_col = 0;

            int act = key < 0 ? key * -1 : key;
            
            while (act != 0)
            {
                if (act < 0) return res;

                const int free_space = cols - new_col;
                int shift = 0;

                if (free_space == 0)
                {
                    shift += 1;
                    new_row = key < 0 ? new_row - 1 : new_row + 1;
                }

                if (act - shift < cols)
                {
                    new_col = key < 0 ? new_col - act : new_col + act;
                    act = 0;
                }
                else
                {
                    new_col = 0;
                    shift += cols;
                }

                if (new_row < 0 || new_row > rows)
                {
                    new_row = key < 0 ? rows : 0;
                }
                
                act -= shift;
            }

            res[new_row][new_col] = table[i][j];
        }
    }

    return res;
}