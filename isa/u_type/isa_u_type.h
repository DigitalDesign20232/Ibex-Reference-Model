#ifndef ISA_U_TYPE_H
#define ISA_U_TYPE_H

#include "ibex_def.h"
#include "isa_def.h"

typedef struct {
    uint8_t opcode;
    void (*instruction)(ibex_system_t*, uint8_t, uint32_t);
} isa_u_handler_t;

int16_t ISA_U_Handler(isa_input_t* input);

void ISA_U_lui(ibex_system_t* ibex_system, uint8_t rd, uint32_t imm);
void ISA_U_auipc(ibex_system_t* ibex_system, uint8_t rd, uint32_t imm);

#endif