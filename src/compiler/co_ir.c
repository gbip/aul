//
// Created by paul on 20/03/19.
//

#include "co_ir.h"
#include "../aul_utils.h"


struct ir_body {
    ir_body* next;
    ir_ins* instr;
};

struct ir_ins {

    union {
        struct ins {
            int op;
            int p1;
            int p2;
        };
        struct _if {
            ir_body* if_cond;
            ir_body* if_body;
        };
    };

};
