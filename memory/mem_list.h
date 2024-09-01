#ifndef MEM_LIST_H
#define MEM_LIST_H

#include "mem_def.h"

struct mem_list_node_t{
    struct mem_list_node_t* next;
    mem_node_t data;
};
typedef struct mem_list_node_t mem_list_node_t;

typedef struct {
    mem_list_node_t* head;
} mem_list_t;

void MEM_LIST_Constructor(mem_list_t* mem_list);
void MEM_LIST_Destructor(mem_list_t* mem_list);
void MEM_LIST_Insert(mem_list_t* mem_list, uint32_t address, uint32_t value);

#endif