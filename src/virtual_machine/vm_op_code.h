//
// Created by paul on 20/03/19.
//

#ifndef AUL_OP_CODE_H
#define AUL_OP_CODE_H

#include <stdint.h>

// Describe all the opcodes implemented by the virtual machine
enum vm_opcode_t {
    ADD,
    SUB,
    MUL,
    DIV,
    LOAD,
    STORE,
    EQ,
    INF,
    INFEQ,
    SUP,
    SUPEQ,
    MOVE,
    COPY,
    PRINT
};

// Give semantic to an integer by mapping it to an opcode
// 0 => MOVE
// 1 => COPY
// etc.
uint8_t OP_CODES[17] = {
        MOVE,
        COPY,
        OP_ADD,
        SUB,
        MUL,
        DIV,
        LOAD,
        STORE,
        EQ,
        INF,
        INFEQ,
        SUP,
        SUPEQ,
        PRINT
};

#endif //AUL_OP_CODE_H
