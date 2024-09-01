#include "../mem_list.h"
#include <stdio.h>

void print_list(mem_list_t* list)
{
    mem_list_node_t* head = list->head;
    while (head) {
        printf("0x%08X | %d\n", head->data.address, head->data.value);
        head = head->next;
    }
}

int main()
{
    mem_list_t list;
    MEM_LIST_Constructor(&list);

    MEM_LIST_Insert(&list, 0x1243AB5F, 12);
    MEM_LIST_Insert(&list, 0x1243AB5F, 32255);
    MEM_LIST_Insert(&list, 0x1243AB5F, 6536);
    MEM_LIST_Insert(&list, 0x1243AB5F, 8932845);
    MEM_LIST_Insert(&list, 0x1243AB5F, 54893);
    MEM_LIST_Insert(&list, 0x1243AB5E, 143);
    MEM_LIST_Insert(&list, 0x1243AB5A, 5235);
    MEM_LIST_Insert(&list, 0x1243AB5A, 325);
    MEM_LIST_Insert(&list, 0x1243AB5A, 325245);
    MEM_LIST_Insert(&list, 0x1243AB5A, 3252);
    MEM_LIST_Insert(&list, 0x1243AB5F, 6536);
    MEM_LIST_Insert(&list, 0x1243AB5F, 32255);
    MEM_LIST_Insert(&list, 0x1243AB5A, 5224535);
    MEM_LIST_Insert(&list, 0x1243AB5E, 14453);
    print_list(&list);
    printf("\nSearch value at address 0x%08X: %d", 0x1243AB5F, MEM_LIST_Search(&list, 0x1243AB5F));

    MEM_LIST_Destructor(&list);
}
