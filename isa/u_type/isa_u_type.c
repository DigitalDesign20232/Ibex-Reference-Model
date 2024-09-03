#include "isa_u_type.h"

isa_u_handler_t isa_u_handler_lut[] = {
    { 0x37, ISA_U_lui },
    { 0x17, ISA_U_auipc },
};

static const uint16_t num_of_isa_u_handler = sizeof(isa_u_handler_lut) / sizeof(isa_u_handler_lut[0]);

int16_t ISA_U_Handler(isa_input_t* input)
{
    isa_u_data_t* isa_u = &input->type.u;

    for (uint16_t i = 0; i < num_of_isa_u_handler; i++) {
        if (isa_u->opcode == isa_u_handler_lut[i].opcode) {
            isa_u_handler_lut[i].instruction(input->ibex_system, isa_u->rd, isa_u->imm);
            return ((int16_t) i);
        }
    }

    return -1;
}

void ISA_U_lui(ibex_system_t* ibex_system, uint8_t rd, uint32_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = imm << 12;
}

void ISA_U_auipc(ibex_system_t* ibex_system, uint8_t rd, uint32_t imm)
{
    uint32_t* reg = ibex_system->ibex_core.reg_file.x;
    reg[rd] = ibex_system->ibex_core.pc + (imm << 12);
}
