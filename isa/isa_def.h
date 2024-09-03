#ifndef ISA_DEF_H
#define ISA_DEF_H

#include "ibex_def.h"
#include "isa_b_type_def.h"
#include "isa_i_type_def.h"
#include "isa_r_type_def.h"
#include "isa_s_type_def.h"
#include "isa_j_type_def.h"

typedef enum {
    ISA_R,
    ISA_I,
    ISA_S,
    ISA_B,
    ISA_J,
} isa_type_t;

typedef union {
    isa_r_data_t r;
    isa_i_data_t i;
    isa_s_data_t s;
    isa_b_data_t b;
    isa_j_data_t j;
} isa_type_data_t;

typedef struct {
    ibex_system_t* ibex_system;
    isa_type_data_t type;
} isa_input_t;

#endif