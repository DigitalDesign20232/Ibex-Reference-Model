#include "mem_list.h"
#include <stdlib.h>

// Constructor for the memory list
void MEM_LIST_Constructor(mem_list_t* mem_list)
{
    mem_list->head = NULL;
}

// Destructor for the memory list
void MEM_LIST_Destructor(mem_list_t* mem_list)
{
    mem_list_node_t* current = mem_list->head;
    while (current != NULL) {
        mem_list_node_t* next = current->next;
        free(current);
        current = next;
    }
    mem_list->head = NULL;
}

// Insert a new node into the memory list in sorted order
void MEM_LIST_Insert(mem_list_t* mem_list, uint32_t address, uint32_t value)
{
    // Create a new node
    mem_list_node_t* new_node = (mem_list_node_t*) malloc(sizeof(mem_list_node_t));
    if (new_node == NULL) {
        // Handle memory allocation failure
        return; // or handle the error as necessary
    }

    // Assign data to the new node
    new_node->data.address = address;
    new_node->data.value = value;
    new_node->next = NULL;

    // Check if the list is empty
    if (mem_list->head == NULL) {
        mem_list->head = new_node;
        return;
    }

    // If the new address is greater than the head's address, insert to the beginning
    if (mem_list->head->data.address > address) {
        new_node->next = mem_list->head;
        mem_list->head = new_node;
        return;
    }

    // If the new address matches the head's address, update the value
    if (mem_list->head->data.address == address) {
        mem_list->head->data.value = value;
        free(new_node); // Free the allocated memory as it's not needed
        return;
    }

    // Insert in sorted order
    mem_list_node_t* current = mem_list->head;
    // Traverse the list to find the correct position
    while (current->next != NULL && current->next->data.address < address) {
        current = current->next;
    }

    // If there's a node with the same address, update the value
    if (current->data.address == address) {
        current->data.value = value;
        free(new_node); // Free the allocated memory as it's not needed
    } else if (current->next != NULL && current->next->data.address == address) {
        current->next->data.value = value;
        free(new_node); // Free the allocated memory as it's not needed
    } else {
        // Insert the new node into the list
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Search for the value corresponding to the given address
uint32_t MEM_LIST_Search(mem_list_t* mem_list, uint32_t address)
{
    mem_list_node_t* current = mem_list->head;

    // Traverse the list to find the node with the specified address
    while (current != NULL) {
        if (current->data.address == address) {
            return current->data.value; // Return the value if found
        }
        if (current->data.address > address) {
            return 0; // Return the value if found
        }
        current = current->next; // Move to the next node
    }

    // If the address is not found, you can return a specific value (e.g., 0)
    // or handle the error as needed. Here we return 0 for simplicity.
    return 0;
}