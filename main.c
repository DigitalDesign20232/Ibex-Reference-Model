#include <stdint.h>
#include <stdio.h>

#include "ibex_def.h"
#include "ibex_system.h"
#include "instruction_decode.h"
#include "instruction_fetch.h"
#include "write_back.h"

int main()
{
    ibex_system_t ibex_system;
    IBEX_SYSTEM_Init(&ibex_system);

    isa_input_t input = {
        .ibex_system = &ibex_system,
    };

    while (1) {
        uint32_t instruction = 0;
        instruction = IF_Fetch();

        int16_t index = ID_Decode(instruction, &input);
        if (index == -1)
            break;

        index = ID_RunInstruction(index, &input);
        if (index == -1)
            break;

        WB_WriteReg(&ibex_system);
    }

    IF_Destructor();
    printf("\nIllegal Instruction");
    printf("\nProgram halted!");
    printf("\n");
    return 0;
}