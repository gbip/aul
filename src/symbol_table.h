//
// Created by paul on 20/03/19.
//

#ifndef AUL_SYMBOL_TABLE_H
#define AUL_SYMBOL_TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include "ast.h"

// The maximum size of our symbol tables
#define TABLE_SIZE 1000

// The type_t of an address on our target
typedef uint64_t target_usize_t;

// The base addresses for our variables
const target_usize_t base_addr = 0x4000;

typedef struct symbol_table_entry symbol_table_entry;

typedef struct ts ts;

// Create a new symbol table
ts* make_ts();

// Add an entry in the symbol table
void ts_add(ts* ts, const char* name, type_t type, uint64_t depth);

// Retrieve the index of a specified entry in the symbol table
target_usize_t ts_get(ts* ts, const char* name);

void step_out_of_block(ts* ts);

#endif //AUL_SYMBOL_TABLE_H