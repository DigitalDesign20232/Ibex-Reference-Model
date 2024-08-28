#ifndef ISA_R_TYPE_H
#define ISA_R_TYPE_H

#include "ibex_def.h"
#include "isa_def.h"

typedef struct {
    uint16_t funct3funct7;
    void (*instruction)(ibex_system_t*, uint8_t, uint8_t, uint8_t);
} isa_r_handler_t;

int16_t ISA_R_Handler(isa_input_t* input);

void ISA_R_add(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2);
void ISA_R_sub(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2);
void ISA_R_xor(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2);
void ISA_R_or(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2);
void ISA_R_and(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2);
void ISA_R_sll(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2);
void ISA_R_srl(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2);
void ISA_R_sra(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2);
void ISA_R_slt(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2);
void ISA_R_sltu(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2);

#endif