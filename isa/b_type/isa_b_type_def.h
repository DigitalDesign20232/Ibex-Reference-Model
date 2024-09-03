#ifndef ISA_B_TYPE_DEF_H
#define ISA_B_TYPE_DEF_H

#include <stdint.h>

typedef struct {
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint16_t imm;
} isa_b_data_t;

#endif