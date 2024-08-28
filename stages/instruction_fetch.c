#include "instruction_fetch.h"

static FILE* imem_file = NULL;

uint32_t IF_Fetch(void)
{
    if (!imem_file)
        imem_file = fopen("data/imem.mem", "r");

    uint8_t instruction_char[33] = { 0 };
    int ret = 0;
    ret = fscanf(imem_file, "%32s", instruction_char);
    fscanf(imem_file, "%*[^\n]%*c");
    if (ret == -1 || ret == EOF) return 0;

    uint32_t instruction = 0;
    for (uint8_t i = 0; i < 32; i++) {
        instruction = instruction | (((uint8_t) (instruction_char[i] - '0')) << (31 - i));
    }

    return instruction;
}

void IF_Destructor(void) {
    fclose(imem_file);
}
