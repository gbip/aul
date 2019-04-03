set(VM_SRC_FILES
        vm_op_code.c
        vm_machine.c
        vm_memory.c vm_main.c)

add_executable(virtual_machine ${VM_SRC_FILES})