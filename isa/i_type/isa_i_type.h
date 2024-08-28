#ifndef ISA_I_TYPE_H
#define ISA_I_TYPE_H

#include "ibex_def.h"
#include "isa_def.h"

typedef struct {
    uint16_t funct3;
    void (*instruction)(ibex_system_t*, uint8_t, uint8_t, uint16_t);
} isa_i_handler_t;

int16_t ISA_I_Handler(isa_input_t* input);

void ISA_I_addi(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);

#endif