#ifndef INSTRUCTION_DECODE_H
#define INSTRUCTION_DECODE_H

#include <stdint.h>
#include "isa_def.h"
#include "isa_r_type.h"

typedef struct {
    uint8_t opcode;
    isa_type_t type;
    int16_t (*instruction_handler)(isa_input_t*);
} instruction_decode_t;

int16_t ID_Decode(uint32_t instruction, isa_input_t* input);
int16_t ID_RunInstruction(int16_t id_lut_index, isa_input_t* input);

#endif