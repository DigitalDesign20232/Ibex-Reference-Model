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
    IBEX_SYSTEM_Constructor(&ibex_system);

    isa_input_t input = {
        .ibex_system = &ibex_system,
    };

    uint32_t instruction = 0;
    while (1) {
        instruction = IF_Fetch(&ibex_system);
        printf("\nFetched Instruction: 0x%X", instruction);

        int16_t index = ID_Decode(instruction, &input);
        if (index == -1)
            break;

        index = ID_RunInstruction(index, &input);
        if (index == -1)
            break;

        WB_WriteReg(&ibex_system);
    }

    printf("\n\nIllegal Instruction: 0x%X", instruction);
    printf("\nProgram halted!");
    printf("\n");

    IBEX_SYSTEM_Destructor(&ibex_system);
    return 0;
}