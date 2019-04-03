//
// Created by paul on 20/03/19.
//

#include "vm_memory.h"
#include <stdio.h>

// The memory is an array
struct vm_mem {
	DATA_TYPE memory[MEMORY_SIZE];
};


DATA_TYPE get_addr(const vm_mem* mem, uint32_t addr) {
	// Check that we are not out of range
	if(addr - MEMORY_OFFSET > MEMORY_SIZE - 1) {
		printf("Out of range memory address (read %#x).", addr);
		return 0;
	}
	return mem->memory[addr - MEMORY_OFFSET];
}
void set_addr(vm_mem* mem, uint32_t addr, DATA_TYPE value) {
	// Check that we are not out of range
	if(addr - MEMORY_OFFSET > MEMORY_SIZE - 1) {
		printf("Out of range memory address (write %#x).", addr);
	} else {
		mem->memory[addr - MEMORY_OFFSET] = value;
	}
}
