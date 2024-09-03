#ifndef IBEX_DEF_H
#define IBEX_DEF_H

#include "mem_list.h"
#include <stdint.h>

typedef struct {
    uint32_t x[32];
} register_file_t;

typedef struct {
    uint32_t pc;
    register_file_t reg_file;
} ibex_core_t;

typedef struct {
    ibex_core_t ibex_core;
    mem_list_t imem;
    mem_list_t dmem;
} ibex_system_t;

#endif