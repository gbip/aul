//
// Created by paul on 20/03/19.
//

#ifndef AUL_MACHINE_H
#define AUL_MACHINE_H

#define INSTR_SIZE 6 // 48 bits

typedef struct vm_machine vm_machine;

void vm_execute( struct vm_machine *vm,const char *filename);
vm_machine* vm_make_machine();


#endif //AUL_MACHINE_H
