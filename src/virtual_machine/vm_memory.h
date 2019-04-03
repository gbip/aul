//
// Created by paul on 20/03/19.
//

#ifndef AUL_MEMORY_H
#define AUL_MEMORY_H


#include <stdint.h>

// Type of the data stored in memory
#define DATA_TYPE uint32_t

// The number of items in the memory
#define MEMORY_SIZE 0x8000

// The offset applied to memory addresses
#define MEMORY_OFFSET 0x000

// A structure that represent the virtual's machine memory
typedef struct vm_mem vm_mem;

// Initialize the memory
vm_mem* vm_make_mem();

// Retrieve data from the memory.
// Returns 0 if the address is out of range
DATA_TYPE get_addr(const vm_mem* mem, uint32_t addr);

// Store data in the memory
// If the address is out of range, does nothing
void set_addr(vm_mem* mem, uint32_t addr, DATA_TYPE value);

#endif // AUL_MEMORY_H
