#include "util_convert.h"

uint32_t UTIL_Convert_BinaryStringToUint32(const uint8_t binary_str[32]) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result <<= 1; // Shift left by 1
        if (binary_str[i] == '1') {
            result |= 1; // Set the least significant bit if the current character is '1'
        }
    }
    return result;
}