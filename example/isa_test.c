#include <stdint.h>
#include <stdio.h>

#include "ibex_def.h"
#include "ibex_system.h"
#include "isa_r_type.h"

void test(ibex_system_t* ibex_system, void isa(ibex_system_t*, uint8_t, uint8_t, uint8_t))
{
    isa(ibex_system, 5, 8, 23);
    printf("\nrs1: %10u %10d %08X", ibex_system->reg_file.x[5], ibex_system->reg_file.x[5], ibex_system->reg_file.x[5]);
    printf("\nrs2: %10u %10d %08X", ibex_system->reg_file.x[8], ibex_system->reg_file.x[8], ibex_system->reg_file.x[8]);
    printf(
        "\nrd:  %10u %10d %08X", ibex_system->reg_file.x[23], ibex_system->reg_file.x[23], ibex_system->reg_file.x[23]);
}

#define TEST(ibex_system, isa_function)                                                                                \
    printf("\n\n%s", #isa_function);                                                                                   \
    test(ibex_system, isa_function);

int main()
{
    ibex_system_t ibex_system;
    IBEX_SYSTEM_Init(&ibex_system);

    ibex_system.reg_file.x[5] = (uint32_t) -12635;
    ibex_system.reg_file.x[8] = (uint32_t) 4;

    TEST(&ibex_system, ISA_R_add);
    TEST(&ibex_system, ISA_R_sub);
    TEST(&ibex_system, ISA_R_xor);
    TEST(&ibex_system, ISA_R_or);
    TEST(&ibex_system, ISA_R_and);
    TEST(&ibex_system, ISA_R_sll);
    TEST(&ibex_system, ISA_R_srl);
    TEST(&ibex_system, ISA_R_sra);
    TEST(&ibex_system, ISA_R_slt);
    TEST(&ibex_system, ISA_R_sltu);
}