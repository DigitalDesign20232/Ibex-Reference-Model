#include "isa_i_type.h"

static void ISA_I_srli_srai(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm);

isa_i_handler_t isa_i_handler_lut[] = {
    { 0x130, ISA_I_addi },
    { 0x134, ISA_I_xori },
    { 0x136, ISA_I_ori },
    { 0x137, ISA_I_andi },
    { 0x131, ISA_I_slli },
    { 0x135, ISA_I_srli_srai },
    { 0x132, ISA_I_slti },
    { 0x133, ISA_I_sltiu },
    { 0x030, ISA_I_lb },
    { 0x031, ISA_I_lh },
    { 0x032, ISA_I_lw },
    { 0x034, ISA_I_lbu },
    { 0x035, ISA_I_lhu },
};

static const uint16_t num_of_isa_i_handler = sizeof(isa_i_handler_lut) / sizeof(isa_i_handler_lut[0]);

int16_t ISA_I_Handler(isa_input_t* input)
{
    isa_i_data_t* isa_i = &input->type.i;

    for (uint16_t i = 0; i < num_of_isa_i_handler; i++) {
        if (isa_i->opcode_funct3 == isa_i_handler_lut[i].opcode_funct3) {
            uint8_t imm5_11 = 0;
            switch (isa_i->opcode_funct3) {
                case 0x131:
                    if ((isa_i->imm >> 5) & 0x7F)
                        return -1;
                    break;

                case 0x135:
                    imm5_11 = (isa_i->imm >> 5) & 0x7F;
                    if (imm5_11 != 0x00 && imm5_11 != 0x20)
                        return -1;

                default:
                    break;
            }
            isa_i_handler_lut[i].instruction(input->ibex_system, isa_i->rd, isa_i->rs1, isa_i->imm);
            return ((int16_t) i);
        }
    }

    return -1;
}

void ISA_I_addi(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    int32_t* reg = (int32_t*) ibex_system->ibex_core.reg_file.x;
    reg[rd] = reg[rs1] + (int32_t) imm;
}

void ISA_I_xori(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = reg[rs1] ^ imm;
}

void ISA_I_ori(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = reg[rs1] | imm;
}

void ISA_I_andi(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = reg[rs1] & imm;
}

void ISA_I_slli(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = reg[rs1] << imm;
}

void ISA_I_srli(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = reg[rs1] >> imm;
}

void ISA_I_srai(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    int32_t* reg = (int32_t*) ibex_system->ibex_core.reg_file.x;
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
    int32_t* reg = (int32_t*) ibex_system->ibex_core.reg_file.x;
    reg[rd] = (reg[rs1] < (int32_t) imm) ? 1L : 0L;
}

void ISA_I_sltiu(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = (reg[rs1] < (uint32_t) imm) ? 1UL : 0UL;
}

void ISA_I_lb(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = (uint32_t) ((int32_t) ((int8_t) ((MEM_LIST_Search(&ibex_system->imem, reg[rs1] + imm)) & 0xFFUL)));
}

void ISA_I_lh(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = (uint32_t) ((int32_t) ((int16_t) ((MEM_LIST_Search(&ibex_system->imem, reg[rs1] + imm)) & 0xFFFFUL)));
}

void ISA_I_lw(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = (uint32_t) ((int32_t) ((MEM_LIST_Search(&ibex_system->imem, reg[rs1] + imm)) & 0xFFFFFFFFUL));
}

void ISA_I_lbu(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = (uint32_t) ((uint8_t) ((MEM_LIST_Search(&ibex_system->imem, reg[rs1] + imm)) & 0xFFUL));
}

void ISA_I_lhu(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = (uint32_t) ((uint16_t) ((MEM_LIST_Search(&ibex_system->imem, reg[rs1] + imm)) & 0xFFFFUL));
}
