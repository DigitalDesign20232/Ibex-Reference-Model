#include "isa_i_type.h"
#include "isa_r_type.h"

static void ISA_I_srli_srai(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);

isa_i_handler_t isa_i_handler_lut[] = {
    { 0x0, ISA_I_addi },
    { 0x4, ISA_I_xori },
    { 0x6, ISA_I_ori },
    { 0x7, ISA_I_andi },
    { 0x1, ISA_I_slli },
    { 0x5, ISA_I_srli_srai },
    { 0x2, ISA_I_slti },
    { 0x3, ISA_I_sltiu },
};

static const uint16_t num_of_isa_i_handler = sizeof(isa_i_handler_lut) / sizeof(isa_i_handler_lut[0]);

int16_t ISA_I_Handler(isa_input_t* input)
{
    isa_i_data_t* r = &input->type.i;

    for (uint16_t i = 0; i < num_of_isa_i_handler; i++) {
        if (input->type.i.funct3 == isa_i_handler_lut[i].funct3) {
            uint8_t imm5_11 = 0;
            switch (input->type.i.funct3) {
                case 0x1:
                    if ((input->type.i.imm >> 5) & 0x7F)
                        return -1;
                    break;

                case 0x5:
                    imm5_11 = (input->type.i.imm >> 5) & 0x7F;
                    if (imm5_11 != 0x00 && imm5_11 != 0x20)
                        return -1;

                default:
                    break;
            }
            isa_i_handler_lut[i].instruction(input->ibex_system, r->rd, r->rs1, r->imm);
            return ((int16_t) i);
        }
    }

    return -1;
}

void ISA_I_addi(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    int32_t* reg = (int32_t*) ibex_system->reg_file.x;
    reg[rd] = reg[rs1] + (int32_t) imm;
}

void ISA_I_xori(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->reg_file.x;
    reg[rd] = reg[rs1] ^ imm;
}

void ISA_I_ori(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->reg_file.x;
    reg[rd] = reg[rs1] | imm;
}

void ISA_I_andi(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->reg_file.x;
    reg[rd] = reg[rs1] & imm;
}

void ISA_I_slli(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->reg_file.x;
    reg[rd] = reg[rs1] << imm;
}

void ISA_I_srli(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->reg_file.x;
    reg[rd] = reg[rs1] >> imm;
}

void ISA_I_srai(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    int32_t* reg = (int32_t*) ibex_system->reg_file.x;
    reg[rd] = reg[rs1] >> imm;
}

static void ISA_I_srli_srai(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint8_t imm5_11 = (imm >> 5) & 0x7F;
    if (imm5_11 == 0x00)
        ISA_I_srli(ibex_system, rd, rs1, imm);
    else if (imm5_11 == 0x20)
        ISA_I_srai(ibex_system, rd, rs1, imm);
}

void ISA_I_slti(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    int32_t* reg = (int32_t*) ibex_system->reg_file.x;
    reg[rd] = (reg[rs1] < (int32_t) imm) ? 1L : 0L;
}

void ISA_I_sltiu(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->reg_file.x;
    reg[rd] = (reg[rs1] < (uint32_t) imm) ? 1UL : 0UL;
}
