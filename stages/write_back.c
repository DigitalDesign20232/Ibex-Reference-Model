#include "write_back.h"
#include <stdio.h>

void WB_WriteReg(ibex_system_t* ibex_system) {
    FILE* regfile_file = NULL;
    regfile_file = fopen("data/register_file.mem", "w");
    for (uint8_t i = 0; i < 32; i++) {
        fprintf(regfile_file, "%d\n", ibex_system->ibex_core.reg_file.x[i]);
    }
    fclose(regfile_file);
 }