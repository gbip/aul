//
// Created by paul on 20/03/19.
//

#include "vm_machine.h"
#include "vm_memory.h"
#include "vm_op_code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

// A virtual machine is some memory associated with some registers
struct vm_machine {
	vm_mem* mem;
	// The registers are represented by an array, where the index represent the register number
	// r0 is regs[0]
	uint32_t regs[32];
};

vm_machine* vm_make_machine() {
	vm_machine* result = malloc(sizeof(vm_machine));
	result->mem = vm_make_mem();
	return result;
}

// Return the 2nd operand in the form of a 32 bit integer
uint32_t vm_instr_get_2nd_operand(uint8_t instr[INSTR_SIZE]) {
	return (instr[2] << 24) + (instr[3] << 16) + (instr[4] << 8) + instr[5];
}

// Return the last byte of the operand, used to index registers
uintptr_t vm_instr_get_rb(uint8_t instr[INSTR_SIZE]) {
	return instr[5];
}

uint8_t* vm_get_binary(const char* filename, uint32_t * nb_instr) {
    uint8_t* result = malloc(sizeof(uint8_t) * INSTR_SIZE * 4096);
    int index = 0;
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        printf("File does not exist");
        free(result);
        return NULL;
    }
    // allocate the buffer where the file content will be stored
    uint8_t instr[INSTR_SIZE];
    // iterate over the whole file
    while(!feof(file)) {
        // load the next instruction in the buffer
        fread(instr, 1, INSTR_SIZE, file);
        memcpy(result + INSTR_SIZE*index,instr, INSTR_SIZE);
        if (feof(file)) {
            break;
        }
        index++;
    }
    *nb_instr = index;
    return result;
}

void vm_execute(struct vm_machine* vm, const char* filename) {
    uint32_t nb_instr;
    uint32_t current_instr = 0;

    uint8_t * code = vm_get_binary(filename, &nb_instr);

	if(code == NULL) {
		printf("File does not exist");
		return;
	}

	uint8_t instr[INSTR_SIZE];
	while(current_instr < nb_instr) {
        memcpy(instr,code + INSTR_SIZE*current_instr, INSTR_SIZE);

		// handle the instruction
		//printf("OPCODE : %#x r%d %#x\n", instr[0], instr[1], vm_instr_get_2nd_operand(instr));
		printf("PC : %#x, R0 : %#x, R1 : %#x | ",current_instr, vm->regs[0], vm->regs[1]);
		switch(OP_CODES[instr[0]]) {
			case MOVE:
			    if(DEBUG)
				    printf("MOVE r%d %#x\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = vm_instr_get_2nd_operand(instr);
				break;
			case COPY:
				vm->regs[instr[1]] = vm->regs[vm_instr_get_rb(instr)];
				break;
			case ADD:
                if(DEBUG)
				    printf("ADD r%d r%u\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = vm->regs[instr[1]] + vm->regs[vm_instr_get_rb(instr)];
				break;
			case SUB:
                if(DEBUG)
				    printf("SUB r%d r%u\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = vm->regs[instr[1]] - vm->regs[vm_instr_get_rb(instr)];
				break;
			case MUL:
                if(DEBUG)
				    printf("MUL r%d r%u\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = vm->regs[instr[1]] * vm->regs[vm_instr_get_rb(instr)];
				break;
			case DIV:
                if(DEBUG)
				    printf("DIV r%d r%u\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = vm->regs[instr[1]] / vm->regs[vm_instr_get_rb(instr)];
				break;
			case EQ:
                if (vm->regs[instr[1]] == vm->regs[vm_instr_get_rb(instr)]){
                    vm->regs[instr[1]] = 1;
                }else {
                    vm->regs[instr[1]] = 0;
                }
                break;
			case INF:
			    printf("INF %d < %d ?\n",vm->regs[instr[1]], vm->regs[vm_instr_get_rb(instr)]);
			    if (vm->regs[instr[1]] < vm->regs[vm_instr_get_rb(instr)]){
                    vm->regs[instr[1]] = 1;
				} else {
                    vm->regs[instr[1]] = 0;
			    }
				break;
			case INFEQ:
                if (vm->regs[instr[1]] <= vm->regs[vm_instr_get_rb(instr)]){
                    vm->regs[instr[1]] = 1;
                } else {
                    vm->regs[instr[1]] = 0;
                }
				break;
			case SUP:
                if (vm->regs[instr[1]] > vm->regs[vm_instr_get_rb(instr)]) {
                    vm->regs[instr[1]] = 1;
                } else {
                    vm->regs[instr[1]] = 0;
                }
                break;
			case SUPEQ:
                if (vm->regs[instr[1]] >= vm->regs[vm_instr_get_rb(instr)]){
                    vm->regs[instr[1]] = 1;
                }else {
                    vm->regs[instr[1]] = 0;
                }
                break;
			case LOAD:
                if(DEBUG)
				    printf("LOAD r%d [%#x]\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = get_addr(vm->mem, vm_instr_get_2nd_operand(instr));
				break;
			case STORE:
                if(DEBUG)
				    printf("STORE r%d [%#x]\n", instr[1], vm_instr_get_2nd_operand(instr));
				set_addr(vm->mem, vm_instr_get_2nd_operand(instr), vm->regs[instr[1]]);
				break;
			case PRINT:
                if(DEBUG)
                    printf("PRINT r%d\n", instr[1]);
                printf("%u \n", vm->regs[instr[1]]);
				break;
		    case JMPCRELADD : {
		        printf("JUMP to %#x if %u is 0\n", current_instr + vm_instr_get_2nd_operand(instr), vm->regs[instr[1]]);
                if (vm->regs[instr[1]] == 0) {
                    printf("Jumping...\n");
                    current_instr += vm_instr_get_2nd_operand(instr) - 1;
                }
		        break;
		    }
		    case JMPRELADD: {
		        printf("JUMP to %#x\n",current_instr + vm_instr_get_2nd_operand(instr));
                current_instr += vm_instr_get_2nd_operand(instr) - 1;
            }
		}
        current_instr++;
    }
}
