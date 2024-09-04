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

    int16_t index;
    uint32_t instruction = 0;
    while (1) {
        instruction = IF_Fetch(&ibex_system);
        printf("\nPC = 0x%X | Fetched Instruction: 0x%X", ibex_system.ibex_core.pc, instruction);

        index = ID_Decode(instruction, &input);
        if (index == -1 || index == -2 || index == -3)
            break;

        index = ID_RunInstruction(index, &input);
        if (index == -1 || index == -2 || index == -3)
            break;

        WB_WriteReg(&ibex_system);
    }

    if (index == -1) {
        printf("\n\nIllegal Instruction: 0x%X", instruction);
        printf("\nProgram halted!");
    } else if (index == -2) {
        printf("\n\nReturn control to OS");
    } else if (index == -3) {
        printf("\n\nReturn control to debugger");
    }
    printf("\n");

    IBEX_SYSTEM_Destructor(&ibex_system);
    return 0;
}