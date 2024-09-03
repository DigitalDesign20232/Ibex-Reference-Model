#include "isa_b_type.h"

isa_b_handler_t isa_b_handler_lut[] = {
    { 0x0, ISA_B_beq },
    { 0x1, ISA_B_bne },
    { 0x4, ISA_B_blt },
    { 0x5, ISA_B_bge },
    { 0x6, ISA_B_bltu },
    { 0x7, ISA_B_bgeu },
};

static const uint16_t num_of_isa_s_handler = sizeof(isa_b_handler_lut) / sizeof(isa_b_handler_lut[0]);

int16_t ISA_B_Handler(isa_input_t* input)
{
    isa_b_data_t* isa_b = &input->type.b;

    for (uint16_t i = 0; i < num_of_isa_s_handler; i++) {
        if (isa_b->funct3 == isa_b_handler_lut[i].funct3) {
            isa_b_handler_lut[i].instruction(input->ibex_system, isa_b->rs1, isa_b->rs2, isa_b->imm);
            return ((int16_t) i);
        }
    }

    return -1;
}

void ISA_B_beq(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    if (reg[rs1] == reg[rs2])
        ibex_system->ibex_core.pc = ibex_system->ibex_core.pc + (int32_t) imm;
}

void ISA_B_bne(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    if (reg[rs1] != reg[rs2])
        ibex_system->ibex_core.pc = ibex_system->ibex_core.pc + (int32_t) imm;
}

void ISA_B_blt(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm)
{
    int32_t* reg = (int32_t*) ibex_system->ibex_core.reg_file.x;
    if (reg[rs1] < reg[rs2])
        ibex_system->ibex_core.pc = ibex_system->ibex_core.pc + (int32_t) imm;
}

void ISA_B_bge(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm)
{
    int32_t* reg = (int32_t*) ibex_system->ibex_core.reg_file.x;
    if (reg[rs1] >= reg[rs2])
        ibex_system->ibex_core.pc = ibex_system->ibex_core.pc + (int32_t) imm;
}

void ISA_B_bltu(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    if (reg[rs1] < reg[rs2])
        ibex_system->ibex_core.pc = ibex_system->ibex_core.pc + (int32_t) imm;
}

void ISA_B_bgeu(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    if (reg[rs1] >= reg[rs2])
        ibex_system->ibex_core.pc = ibex_system->ibex_core.pc + (int32_t) imm;
}
