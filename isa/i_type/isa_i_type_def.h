#ifndef ISA_I_TYPE_DEF_H
#define ISA_I_TYPE_DEF_H

#include <stdint.h>

typedef struct {
    uint8_t funct3;
    uint8_t rd;
    uint8_t rs1;
    uint16_t imm;
} isa_i_data_t;

#endif