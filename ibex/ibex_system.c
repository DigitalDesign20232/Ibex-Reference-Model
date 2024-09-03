#include "ibex_system.h"
#include "util_convert.h"
#include <stdio.h>

void IBEX_SYSTEM_Init(ibex_system_t* ibex_system)
{
    IBEX_SYSTEM_RegisterFile_Init(&ibex_system->reg_file);
    IBEX_SYSTEM_Imem_Init(&ibex_system->imem);
    IBEX_SYSTEM_Dmem_Init(&ibex_system->imem);
}

void IBEX_SYSTEM_RegisterFile_Init(register_file_t* reg_file)
{
    FILE* regfile_file = NULL;
    regfile_file = fopen("data/register_file.mem", "r");
    for (uint8_t i = 0; i < 32; i++) {
        fscanf(regfile_file, "%u", &reg_file->x[i]);
    }
    fclose(regfile_file);
}

void IBEX_SYSTEM_Imem_Init(mem_list_t* imem)
{
    MEM_LIST_Constructor(imem);

    FILE* file = fopen("data/imem.mem", "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char line[66];
    uint32_t address;
    uint8_t instruction_char[33]; // 32 characters + null terminator

    while (fgets(line, 66, file)) {
        // Parse the line
        if (sscanf(line, "0x%X,%32s", &address, instruction_char) != 2) {
            fprintf(stderr, "Invalid line format: %s", line);
            continue;
        }

        // Ensure that the binary string is exactly 32 characters
        if (instruction_char[32] != '\0') {
            fprintf(stderr, "Invalid binary string length: %s", instruction_char);
            continue;
        }

        // Convert binary string to uint32_t
        uint32_t instruction_value = UTIL_Convert_BinaryStringToUint32(instruction_char);

        // Print the parsed values
        printf("\nIMEM Address: 0x%X, IMEM Instruction Binary: %s, IMEM Instruction Value: 0x%X", address, instruction_char, instruction_value);
        MEM_LIST_Insert(imem, address, instruction_value);
    }

    fclose(file);
}

void IBEX_SYSTEM_Dmem_Init(mem_list_t* dmem)
{
    MEM_LIST_Constructor(dmem);

    FILE* file = fopen("data/dmem.mem", "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char line[66];
    uint32_t address;
    uint32_t data_value;

    while (fgets(line, 66, file)) {
        // Parse the line
        if (sscanf(line, "0x%X,0x%X", &address, &data_value) != 2) {
            fprintf(stderr, "Invalid line format: %s", line);
            continue;
        }

        // Print the parsed values
        printf("\nDMEM Address: 0x%X, DMEM Value: 0x%X\n", address, data_value);
        MEM_LIST_Insert(dmem, address, data_value);
    }

    fclose(file);
}
