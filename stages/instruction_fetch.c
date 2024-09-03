#include "instruction_fetch.h"

uint32_t IF_Fetch(ibex_system_t* ibex_system)
{
    return MEM_LIST_Search(&ibex_system->imem, ibex_system->ibex_core.pc);
}
