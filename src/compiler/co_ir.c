//
// Created by paul on 20/03/19.
//

#include <stdint.h>
#include "co_ir.h"
#include "../aul_utils.h"
#include "../virtual_machine/vm_op_code.h"


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

ir_body* ir_build_tree(ast_body* ast) {
    
}
