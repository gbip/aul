//
// Created by paul on 20/03/19.
//

#ifndef AUL_OP_CODE_H
#define AUL_OP_CODE_H

#include <stdint.h>

enum OPCODE {
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
    COPY
};

uint8_t OP_CODES[16] = {
        MOVE,
        COPY,
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
        SUPEQ
};

#endif //AUL_OP_CODE_H
