#ifndef ISA_I_TYPE_H
#define ISA_I_TYPE_H

#include "ibex_def.h"
#include "isa_def.h"

typedef struct {
    uint32_t opcode_funct3;
    void (*instruction)(ibex_system_t*, uint8_t, uint8_t, uint16_t);
} isa_i_handler_t;

int16_t ISA_I_Handler(isa_input_t* input);

void ISA_I_addi(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_xori(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_ori(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_andi(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_slli(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_srli(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_srai(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_slti(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_sltiu(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);

void ISA_I_lb(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_lh(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_lw(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_lbu(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);
void ISA_I_lhu(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);

#endif