//
// Created by paul on 20/03/19.
//

#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "co_ir.h"
#include "../aul_utils.h"
#include "../virtual_machine/vm_op_code.h"
#include "../virtual_machine/vm_machine.h"


struct ir_body {
    ir_body* next;
    ir_ins* instr;
};

struct ir_ins {
    enum vm_opcode_t opcode;
    uint8_t op1;
    uint32_t op2;
        /*
        struct _if {
            ir_body* if_cond;
            ir_body* if_body;
        };*/
};

void ir_write_to_file(const char *filename, ir_body *root) {
    uint8_t buffer[INSTR_SIZE] = {0};

    FILE* output = fopen(filename ,"w");

    if (output == NULL) {
        printf("Failed to open %s for writing : %s", filename, strerror(errno));
        return;
    }

    while (root != NULL) {
        buffer[0] = vm_opcode_to_byte(root->instr->opcode);
        buffer[1] = root->instr->op1;
        for (int i=0; i<4 ;++i)
            buffer[i+2] = ((uint8_t*)&root->instr->op2)[3-i];

        fwrite(buffer,1,sizeof(buffer),output);
        root = root->next;
    }

    fclose(output);

}

ir_body* ir_build_tree(ast_body* anAst) {

}
