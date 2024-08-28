#include "isa_i_type.h"
#include "isa_r_type.h"

isa_i_handler_t isa_i_handler_lut[] = {
    { 0x0, ISA_I_addi },
};

static const uint16_t num_of_isa_i_handler = sizeof(isa_i_handler_lut) / sizeof(isa_i_handler_lut[0]);

int16_t ISA_I_Handler(isa_input_t* input)
{
    isa_i_data_t* r = &input->type.i;

    for (uint16_t i = 0; i < num_of_isa_i_handler; i++) {
        if (input->type.i.funct3 == isa_i_handler_lut[i].funct3) {
            isa_i_handler_lut[i].instruction(input->ibex_system, r->rd, r->rs1, r->imm);
            return ((int16_t) i);
        }
    }

    return -1;
}

void ISA_I_addi(ibex_system_t* ibex_system, uint8_t rd, uint8_t rs1, uint16_t imm)
{
    int32_t* reg = (int32_t*) ibex_system->reg_file.x;
    reg[rd] = reg[rs1] + imm;
}