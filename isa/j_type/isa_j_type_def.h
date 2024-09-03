#ifndef ISA_J_TYPE_DEF_H
#define ISA_J_TYPE_DEF_H

#include <stdint.h>

typedef struct {
    uint8_t rd;
    uint32_t imm;
} isa_j_data_t;

#endif