#ifndef ISA_J_TYPE_H
#define ISA_J_TYPE_H

#include "ibex_def.h"
#include "isa_def.h"

typedef struct {
    void (*instruction)(ibex_system_t*, uint8_t, uint32_t);
} isa_j_handler_t;

int16_t ISA_J_Handler(isa_input_t* input);

void ISA_J_jal(ibex_system_t* ibex_system, uint8_t rd, uint32_t imm);

#endif