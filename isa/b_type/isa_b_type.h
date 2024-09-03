#ifndef ISA_B_TYPE_H
#define ISA_B_TYPE_H

#include "ibex_def.h"
#include "isa_def.h"

typedef struct {
    uint8_t funct3;
    void (*instruction)(ibex_system_t*, uint8_t, uint8_t, uint16_t);
} isa_b_handler_t;

int16_t ISA_B_Handler(isa_input_t* input);

void ISA_B_beq(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm);
void ISA_B_bne(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm);
void ISA_B_blt(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm);
void ISA_B_bge(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm);
void ISA_B_bltu(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm);
void ISA_B_bgeu(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm);

#endif