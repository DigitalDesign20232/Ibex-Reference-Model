#ifndef ISA_S_TYPE_DEF_H
#define ISA_S_TYPE_DEF_H

#include <stdint.h>

typedef struct {
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint16_t imm;
} isa_s_data_t;

#endif