#include "instruction_decode.h"

instruction_decode_t id_lut[] = {
    { 0x33, ISA_R, ISA_R_Handler },
    { 0x13, ISA_I, ISA_I_Handler },
    { 0x03, ISA_I, ISA_I_Handler },
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

    switch (id_lut[id_lut_index].type) {
        case ISA_R:
            input->type.r.funct3funct7 = (((instruction >> 12) & 0x3) << 8) | ((instruction >> 25) & 0x3F);
            input->type.r.rd = (instruction >> 7) & 0x1F;
            input->type.r.rs1 = (instruction >> 15) & 0x1F;
            input->type.r.rs2 = (instruction >> 20) & 0x1F;
            break;

        case ISA_I:
            input->type.i.opcode_funct3 = ((instruction & 0x3F) << 4) | ((instruction >> 12) & 0x3);
            input->type.i.rd = (instruction >> 7) & 0x1F;
            input->type.i.rs1 = (instruction >> 15) & 0x1F;
            input->type.i.imm = (uint16_t) ((instruction >> 20) & 0xFFF);

        default:
            break;
    }

    return id_lut_index;
}

int16_t ID_RunInstruction(int16_t id_lut_index, isa_input_t* input)
{
    return id_lut[id_lut_index].instruction_handler(input);
}