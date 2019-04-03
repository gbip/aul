//
// Created by paul on 20/03/19.
//

#include "vm_machine.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Usage : %s <file>\n", argv[0]);
		return 1;
	}
	vm_machine* vm = vm_make_machine();
	vm_execute(vm, argv[2]);
	return 0;
}