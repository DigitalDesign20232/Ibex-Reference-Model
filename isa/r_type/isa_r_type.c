#include "isa_r_type.h"

isa_r_handler_t isa_r_handler_lut[] = {
    { 0x000, ISA_R_add },
    { 0x020, ISA_R_sub },
    { 0x400, ISA_R_xor },
    { 0x600, ISA_R_or },
    { 0x700, ISA_R_and },
    { 0x100, ISA_R_sll },
    { 0x500, ISA_R_srl },
    { 0x520, ISA_R_sra },
    { 0x200, ISA_R_slt },
    { 0x300, ISA_R_sltu },
};

static const uint16_t num_of_isa_r_handler = sizeof(isa_r_handler_lut) / sizeof(isa_r_handler_lut[0]);

int16_t ISA_R_Handler(isa_input_t* input)
{
    isa_r_data_t* r = &input->type.r;

    for (uint16_t i = 0; i < num_of_isa_r_handler; i++) {
        if (input->type.r.funct3funct7 == isa_r_handler_lut[i].funct3funct7) {
            isa_r_handler_lut[i].instruction(input->ibex_system, r->rd, r->rs1, r->rs2);
            return ((int16_t) i);
        }
    }

    return -1;
}

void ISA_R_add(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    int32_t* reg = (int32_t*) ibex_system->reg_file.x;
    reg[rd] = reg[rs1] + reg[rs2];
}

void ISA_R_sub(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    int32_t* reg = (int32_t*) ibex_system->reg_file.x;
    reg[rd] = reg[rs1] - reg[rs2];
}

void ISA_R_xor(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    int32_t* reg = (int32_t*) ibex_system->reg_file.x;
    reg[rd] = reg[rs1] ^ reg[rs2];
}

void ISA_R_or(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    int32_t* reg = (int32_t*) ibex_system->reg_file.x;
    reg[rd] = reg[rs1] | reg[rs2];
}

void ISA_R_and(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    int32_t* reg = (int32_t*) ibex_system->reg_file.x;
    reg[rd] = reg[rs1] & reg[rs2];
}

void ISA_R_sll(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    uint32_t* reg = ibex_system->reg_file.x;
    reg[rd] = reg[rs1] << reg[rs2];
}

void ISA_R_srl(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    uint32_t* reg = ibex_system->reg_file.x;
    reg[rd] = reg[rs1] >> reg[rs2];
}

void ISA_R_sra(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    int32_t* reg = (int32_t*) ibex_system->reg_file.x;
    reg[rd] = reg[rs1] >> reg[rs2];
}

void ISA_R_slt(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    int32_t* reg = (int32_t*) ibex_system->reg_file.x;
    reg[rd] = (reg[rs1] < reg[rs2]) ? 1L : 0L;
}

void ISA_R_sltu(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint8_t rs2)
{
    uint32_t* reg = ibex_system->reg_file.x;
    reg[rd] = (reg[rs1] < reg[rs2]) ? 1UL : 0UL;
}