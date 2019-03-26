//
// Created by paul on 20/03/19.
//

#ifndef AUL_SYMBOL_TABLE_H
#define AUL_SYMBOL_TABLE_H

#include <stdint.h>
#include "co_ast.h"

// The maximum size of our symbol tables
#define TABLE_SIZE 1000

// The base addresses for our variables
#define BASE_ADDR 0x4000

// The co_type_t of an address on our target
typedef uint64_t target_usize_t;

typedef struct symbol_table_entry symbol_table_entry;

typedef struct ts ts;

// Create a new symbol table
ts* ts_make();

// Free the memory allocated by a symbol table
void ts_free(ts *ts);

// Add an entry in the symbol table
void ts_add(ts* ts, const char* name, co_type_t type, uint64_t depth);

uintptr_t ts_gen_tmp(ts* ts, int depth);

uint32_t ts_get_tmp(ts* ts, uintptr_t index);

void ts_free_tmp(ts* ts);

// Retrieve the index of a specified entry in the symbol table
target_usize_t* ts_get(ts* ts, const char* name);

void ts_pop_current_depth(ts *ts);

#endif //AUL_SYMBOL_TABLE_H