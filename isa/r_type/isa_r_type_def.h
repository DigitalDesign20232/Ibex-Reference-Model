#ifndef ISA_R_TYPE_DEF_H
#define ISA_R_TYPE_DEF_H

#include <stdint.h>

typedef struct {
    uint16_t funct3funct7;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
} isa_r_data_t;

#endif