#include "isa_j_type.h"

isa_j_handler_t isa_j_handler_lut[] = {
    { ISA_J_jal },
};

// static const uint16_t num_of_isa_j_handler = sizeof(isa_j_handler_lut) / sizeof(isa_j_handler_lut[0]);

int16_t ISA_J_Handler(isa_input_t* input)
{
    isa_j_handler_lut[0].instruction(input->ibex_system, input->type.j.rd, input->type.j.imm);
    return 0;
}

void ISA_J_jal(ibex_system_t* ibex_system, uint8_t rd, uint32_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = ibex_system->ibex_core.pc + 4;
    ibex_system->ibex_core.pc = (uint32_t) ((int32_t) ibex_system->ibex_core.pc + (int32_t) imm);
}
