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
#include "co_ast_private.h"

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

ir_body* make_body(vm_opcode_t code, uint8_t op1, uint32_t op2, ir_body* following) {
    ir_ins* ins = malloc(sizeof(ir_ins));
    ins->opcode = code;
    ins->op1 = op1;
    ins->op2 = op2;
    ir_body* result = malloc(sizeof(ir_body));
    result->instr = ins;
    result->next = following;
    return result;
}

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

/*
ir_body* ir_build_tree(ast_body* ast) {

}
*/


ir_body** ir_build_instr(ir_body** p, ast_instr* ast, ts* ts) {

}

ir_body** ir_build_instrs(ir_body** p, ast_body* ast, ts* ts) {
    p = ir_build_instr(p, ast->instr, ts);
    if (ast->next != NULL)
        p = ir_build_instrs(p, ast->next, ts);
    return p;
}

/*
ir_body* ir_build_expr(ast_expr* ast, ir_body* ir, ts* ts) {
    switch (ast->det) {
        case OP : {

            uintptr_t a = ts_gen_tmp(ts, 0);
            uintptr_t b = ts_gen_tmp(ts, 0);

            ir_body* load_addr_a = make_body(LOAD, 0, ts_get_tmp(ts,a));
            ir_body* load_addr_b = make_body(LOAD, 1, ts_get_tmp(ts,b));

            ir_body *op = make_body(ADD,0,1,NULL);



            switch (ast->op->op) {
                case OP_ADD : {op->instr->opcode = ADD; break;}
                case OP_SUB : {op->instr->opcode = SUB; break;}
                case OP_DIV : {op->instr->opcode = DIV; break;}
                case OP_MUL : {op->instr->opcode = MUL; break;}
            }
            ir->next = op;
            ir->next = ir_build_expr(ast->op->left, ir_build_expr(ast->op->right, op, ts), ts);
            break;
        }
        case ID :
            break;
        case LIT : {
            ir_body *body = make_body(MOVE, 0, ast->literral, NULL);
            ir->next = body;
            break;
        }
    }
}
 */