#ifndef ISA_DEF_H
#define ISA_DEF_H

#include "ibex_def.h"
#include "isa_r_type_def.h"
#include "isa_i_type_def.h"

typedef enum {
    ISA_R,
    ISA_I
} isa_type_t;

typedef struct {
    ibex_system_t* ibex_system;
    union {
        isa_r_data_t r;
        isa_i_data_t i;
    } type;
} isa_input_t;

#endif