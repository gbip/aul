//
// Created by paul on 20/03/19.
//

#include "vm_machine.h"
#include "vm_memory.h"
#include "vm_op_code.h"
#include <stdio.h>
#include <stdlib.h>

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


void vm_execute(struct vm_machine* vm, const char* filename) {
	// open the file
	FILE* file = fopen(filename, "r");
	if(file == NULL) {
		printf("File does not exist");
		return;
	}
	// allocate the buffer where the file content will be stored
	uint8_t instr[INSTR_SIZE];
	// iterate over the whole file
	while(!feof(file)) {
		// load the next instruction in the buffer
		fread(instr, 1, INSTR_SIZE, file);
		// handle the instruction
		// printf("OPCODE : %#x r%d %#x\n", instr[0], instr[1], vm_instr_get_2nd_operand(instr));
		switch(OP_CODES[instr[0]]) {
			case MOVE:
				printf("MOVE r%d %#x\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = vm_instr_get_2nd_operand(instr);
				break;
			case COPY:
				vm->regs[instr[1]] = vm->regs[vm_instr_get_rb(instr)];
				break;
			case ADD:
				printf("ADD r%d r%u\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = vm->regs[instr[1]] + vm->regs[vm_instr_get_rb(instr)];
				break;
			case SUB:
				printf("SUB r%d r%u\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = vm->regs[instr[1]] - vm->regs[vm_instr_get_rb(instr)];
				break;
			case MUL:
				printf("MUL r%d r%u\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = vm->regs[instr[1]] * vm->regs[vm_instr_get_rb(instr)];
				break;
			case DIV:
				printf("DIV r%d r%u\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = vm->regs[instr[1]] / vm->regs[vm_instr_get_rb(instr)];
				break;
			case EQ:
				vm->regs[instr[1]] = (uint32_t)(vm->regs[instr[1]] == vm->regs[vm_instr_get_rb(instr)]);
				break;
			case INF:
				vm->regs[instr[1]] = (uint32_t)(vm->regs[instr[1]] < vm->regs[vm_instr_get_rb(instr)]);
				break;
			case INFEQ:
				vm->regs[instr[1]] = (uint32_t)(vm->regs[instr[1]] <= vm->regs[vm_instr_get_rb(instr)]);
				break;
			case SUP:
				vm->regs[instr[1]] = (uint32_t)(vm->regs[instr[1]] > vm->regs[vm_instr_get_rb(instr)]);
				break;
			case SUPEQ:
				vm->regs[instr[1]] = (uint32_t)(vm->regs[instr[1]] >= vm->regs[vm_instr_get_rb(instr)]);
				break;
			case LOAD:
				printf("LOAD r%d [%#x]\n", instr[1], vm_instr_get_2nd_operand(instr));
				vm->regs[instr[1]] = get_addr(vm->mem, vm_instr_get_2nd_operand(instr));
				break;
			case STORE:
				printf("STORE r%d [%#x]\n", instr[1], vm_instr_get_2nd_operand(instr));
				set_addr(vm->mem, vm_instr_get_2nd_operand(instr), vm_instr_get_2nd_operand(instr));
				break;
			case PRINT:
				printf("PRINT r%d\n", instr[1]);
				printf("Value of r%u : %u \n", instr[1], vm->regs[instr[1]]);
		}
	}
}
