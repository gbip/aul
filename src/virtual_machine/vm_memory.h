//
// Created by paul on 20/03/19.
//

#ifndef AUL_MEMORY_H
#define AUL_MEMORY_H


#include <stdint.h>

#define DATA_TYPE uint32_t
#define MEMORY_SIZE 0x8000
#define MEMORY_OFFSET 0x000

typedef struct vm_mem vm_mem;

DATA_TYPE get_addr(const vm_mem* mem,uint32_t addr);
void set_addr(vm_mem* mem,uint32_t addr, DATA_TYPE value);

#endif //AUL_MEMORY_H
