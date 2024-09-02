#include "instruction_fetch.h"

uint32_t IF_Fetch(ibex_system_t* ibex_system)
{
    static mem_list_node_t* node = NULL;
    if (!node) node = ibex_system->imem.head;
    else if (!node->next) return 0;
    else node = node->next;

    return node->data.value;
}

void IF_Destructor(void) {

}
