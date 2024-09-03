#ifndef ISA_U_TYPE_DEF_H
#define ISA_U_TYPE_DEF_H

#include <stdint.h>

typedef struct {
    uint8_t opcode;
    uint8_t rd;
    uint32_t imm;
} isa_u_data_t;

#endif