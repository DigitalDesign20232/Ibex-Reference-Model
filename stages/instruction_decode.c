#include "instruction_decode.h"
#include "isa_b_type.h"
#include "isa_i_type.h"
#include "isa_j_type.h"
#include "isa_r_type.h"
#include "isa_s_type.h"
#include "isa_u_type.h"

instruction_decode_t id_lut[] = {
    { 0x33, ISA_R, ISA_R_Handler },
    { 0x13, ISA_I, ISA_I_Handler },
    { 0x03, ISA_I, ISA_I_Handler },
    { 0x67, ISA_I, ISA_I_Handler },
    { 0x23, ISA_S, ISA_S_Handler },
    { 0x63, ISA_B, ISA_B_Handler },
    { 0x6F, ISA_J, ISA_J_Handler },
    { 0x37, ISA_U, ISA_U_Handler },
    { 0x17, ISA_U, ISA_U_Handler },
};
static const uint16_t id_lut_size = sizeof(id_lut) / sizeof(id_lut[0]);

int16_t ID_Decode(uint32_t instruction, isa_input_t* input)
{
    int16_t id_lut_index = -1;
    uint8_t opcode = (instruction & 0x7FUL);
    for (uint16_t i = 0; i < id_lut_size; i++) {
        if (opcode == id_lut[i].opcode) {
            id_lut_index = (int16_t) i;
            break;
        }
    }

    if (id_lut_index == -1)
        return -1;

    input->type = (isa_type_data_t) { 0 };
    switch (id_lut[id_lut_index].type) {
        case ISA_R:
            input->type.r.funct3funct7 = (((instruction >> 12) & 0x7) << 8) | ((instruction >> 25) & 0x3F);
            input->type.r.rd = (instruction >> 7) & 0x1F;
            input->type.r.rs1 = (instruction >> 15) & 0x1F;
            input->type.r.rs2 = (instruction >> 20) & 0x1F;
            break;

        case ISA_I:
            input->type.i.opcode_funct3 = ((instruction & 0x7F) << 4) | ((instruction >> 12) & 0x7);
            input->type.i.rd = (instruction >> 7) & 0x1F;
            input->type.i.rs1 = (instruction >> 15) & 0x1F;
            input->type.i.imm = (uint16_t) ((instruction >> 20) & 0xFFF);
            input->type.i.imm = (input->type.i.imm & 0x800U) ? (input->type.i.imm | 0xF000U) : input->type.i.imm;
            break;

        case ISA_S:
            input->type.s.funct3 = (instruction >> 12) & 0x7;
            input->type.s.rs1 = (instruction >> 15) & 0x1F;
            input->type.s.rs2 = (instruction >> 20) & 0x1F;
            input->type.s.imm = (uint16_t) (((instruction >> 25) & 0x7F) << 5) | ((instruction >> 7) & 0x1F);
            input->type.s.imm = (input->type.s.imm & 0x800U) ? (input->type.s.imm | 0xF000U) : input->type.s.imm;
            break;

        case ISA_B:
            input->type.b.funct3 = (instruction >> 12) & 0x7;
            input->type.b.rs1 = (instruction >> 15) & 0x1F;
            input->type.b.rs2 = (instruction >> 20) & 0x1F;
            input->type.b.imm = (uint16_t) ((((instruction >> 31) & 0x1) << 12) | // imm[12]
                (((instruction >> 7) & 0x1) << 11) | // imm[11]
                (((instruction >> 25) & 0x3F) << 5) | // imm[10:5]
                (((instruction >> 8) & 0xF) << 1)); // imm[4:1]
            input->type.b.imm = (input->type.b.imm & 0x1000U) ? (input->type.b.imm | 0xE000U) : input->type.b.imm;
            break;

        case ISA_J:
            input->type.j.rd = (instruction >> 7) & 0x1F;
            input->type.j.imm = (uint32_t) ((((instruction >> 31) & 0x1) << 20) | (((instruction >> 12) & 0xFF) << 12)
                | (((instruction >> 20) & 0x1) << 11) | (((instruction >> 21) & 0x3FF) << 1));
            input->type.j.imm = (input->type.j.imm & 0x100000U) ? (input->type.j.imm | 0xFFE00000U) : input->type.j.imm;
            break;

        case ISA_U:
            input->type.u.opcode = (instruction & 0x7F);
            input->type.u.rd = (instruction >> 7) & 0x1F;
            input->type.u.imm = (instruction >> 12) & 0xFFFFFUL;
            input->type.u.imm = (input->type.u.imm & 0x80000U) ? (input->type.u.imm | 0xFFF00000U) : input->type.u.imm;
            break;

        default:
            break;
    }

    return id_lut_index;
}

int16_t ID_RunInstruction(int16_t id_lut_index, isa_input_t* input)
{
    uint32_t current_pc = input->ibex_system->ibex_core.pc;
    int16_t index = id_lut[id_lut_index].instruction_handler(input);
    if (current_pc == input->ibex_system->ibex_core.pc)
        input->ibex_system->ibex_core.pc += 4;
    input->ibex_system->ibex_core.reg_file.x[0] = 0;
    return index;
}