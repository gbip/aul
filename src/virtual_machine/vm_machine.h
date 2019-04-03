//
// Created by paul on 20/03/19.
//

#ifndef AUL_MACHINE_H
#define AUL_MACHINE_H

// The size of an instructions in bytes
#define INSTR_SIZE 6 // 48 bits

// A structure that represents our virtual machine
typedef struct vm_machine vm_machine;

// Load some code from a file and execute it
void vm_execute(struct vm_machine* vm, const char* filename);

// Allocate a virtual machine
vm_machine* vm_make_machine();


#endif // AUL_MACHINE_H
