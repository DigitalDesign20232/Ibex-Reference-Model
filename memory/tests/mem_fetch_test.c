#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 66 // 32 hex + comma + 32 binary + null terminator

// Function to convert binary string to uint32_t
uint32_t binaryStringToUint32(const uint8_t *binary_str) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result <<= 1; // Shift left by 1
        if (binary_str[i] == '1') {
            result |= 1; // Set the least significant bit if the current character is '1'
        }
    }
    return result;
}

int main() {
    FILE *file = fopen("../../data/imem.mem", "r");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char line[LINE_LENGTH];
    uint32_t hex_number;
    uint8_t instruction_char[33]; // 32 characters + null terminator

    while (fgets(line, LINE_LENGTH, file)) {
        // Parse the line
        if (sscanf(line, "0x%X,%32s", &hex_number, instruction_char) != 2) {
            fprintf(stderr, "Invalid line format: %s", line);
            continue;
        }

        // Ensure that the binary string is exactly 32 characters
        if (instruction_char[32] != '\0') {
            fprintf(stderr, "Invalid binary string length: %s", instruction_char);
            continue;
        }

        // Convert binary string to uint32_t
        uint32_t instruction_value = binaryStringToUint32(instruction_char);

        // Print the parsed values
        printf("Hex: 0x%X, Binary: %s, Instruction Value: %u\n", hex_number, instruction_char, instruction_value);
    }

    fclose(file);
    return EXIT_SUCCESS;
}