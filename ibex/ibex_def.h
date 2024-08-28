#ifndef IBEX_DEF_H
#define IBEX_DEF_H

#include <stdint.h>

typedef struct {
    uint32_t x[32];
} register_file_t;

typedef struct {
    register_file_t reg_file;
} ibex_system_t;

#endif