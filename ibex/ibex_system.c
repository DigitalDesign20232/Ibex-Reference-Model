#include "ibex_system.h"
#include <stdio.h>

void IBEX_SYSTEM_Init(ibex_system_t* ibex_system)
{
    FILE* regfile_file = NULL;
    regfile_file = fopen("data/register_file.mem", "r");
    for (uint8_t i = 0; i < 32; i++) {
        fscanf(regfile_file, "%u", &ibex_system->reg_file.x[i]);
    }
    fclose(regfile_file);
}