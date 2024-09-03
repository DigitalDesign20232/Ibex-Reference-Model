#include "isa_b_type.h"

isa_b_handler_t isa_b_handler_lut[] = {
    { 0x0, ISA_B_beq },
};

static const uint16_t num_of_isa_s_handler = sizeof(isa_b_handler_lut) / sizeof(isa_b_handler_lut[0]);

int16_t ISA_B_Handler(isa_input_t* input)
{
    isa_s_data_t* isa_s = &input->type.s;

    for (uint16_t i = 0; i < num_of_isa_s_handler; i++) {
        if (isa_s->funct3 == isa_b_handler_lut[i].funct3) {
            isa_b_handler_lut[i].instruction(input->ibex_system, isa_s->rs1, isa_s->rs2, isa_s->imm);
            return ((int16_t) i);
        }
    }

    return -1;
}

void ISA_B_beq(ibex_system_t* ibex_system, uint8_t rs1, uint8_t rs2, uint16_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    if (reg[rs1] == reg[rs2])
        ibex_system->ibex_core.pc += imm;
}
