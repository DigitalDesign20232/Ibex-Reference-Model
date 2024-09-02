#ifndef IBEX_DEF_H
#define IBEX_DEF_H

#include <stdint.h>
#include "mem_list.h"

typedef struct {
    uint32_t x[32];
} register_file_t;

typedef struct {
    register_file_t reg_file;
    mem_list_t imem;
    mem_list_t dmem;
} ibex_system_t;

#endif