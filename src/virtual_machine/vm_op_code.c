//
// Created by paul on 26/03/19.
//

#include "vm_op_code.h"

const uint8_t OP_CODES[17] = {MOVE, COPY, ADD, SUB, MUL, DIV, LOAD, STORE, EQ, INF, INFEQ, SUP, SUPEQ, PRINT};

uint8_t vm_opcode_to_byte(vm_opcode_t op) {
	switch(op) {
		case MOVE:
			return 0x00;
		case COPY:
			return 0x01;
		case LOAD:
			return 0x06;
		case STORE:
			return 0x07;
		case ADD:
			return 0x02;
		case SUB:
			return 0x03;
		case MUL:
			return 0x04;
		case DIV:
			return 0x05;
		case EQ:
			return 0x08;
		case INF:
			return 0x09;
		case INFEQ:
			return 0x0A;
		case SUP:
			return 0x0B;
		case SUPEQ:
			return 0x0C;
		case PRINT:
			return 0x0D;
		default:
			return 0xFF;
	}
}

const char* vm_opcode_to_str(vm_opcode_t op) {
    switch(op) {
        case MOVE:
            return "MOV";
        case COPY:
            return "COPY";
        case LOAD:
            return "LD";
        case STORE:
            return "STR";
        case ADD:
            return "ADD";
        case SUB:
            return "SUB";
        case MUL:
            return "MUL";
        case DIV:
            return "DIV";
        case EQ:
            return "EQ";
        case INF:
            return "INF";
        case INFEQ:
            return "INFEQ";
        case SUP:
            return "SUP";
        case SUPEQ:
            return "SUPEQ";
        case PRINT:
            return "PRINT";
        default:
            return "";
    }
}