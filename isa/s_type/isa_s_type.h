#ifndef ISA_S_TYPE_H
#define ISA_S_TYPE_H

#include "ibex_def.h"
#include "isa_def.h"

typedef struct {
    uint8_t funct3;
    void (*instruction)(ibex_system_t*, uint8_t, uint8_t, uint16_t);
} isa_s_handler_t;

int16_t ISA_S_Handler(isa_input_t* input);

void ISA_S_sb(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm);

#endif