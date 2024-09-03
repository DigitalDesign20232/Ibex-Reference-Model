#ifndef IBEX_SYSTEM_H
#define IBEX_SYSTEM_H

#include "ibex_def.h"

void IBEX_SYSTEM_Init(ibex_system_t* ibex_system);
void IBEX_SYSTEM_RegisterFile_Init(register_file_t* reg_file);
void IBEX_SYSTEM_Imem_Init(mem_list_t* imem);
void IBEX_SYSTEM_Dmem_Init(mem_list_t* dmem);

#endif