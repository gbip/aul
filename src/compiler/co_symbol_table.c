//
// Created by paul on 20/03/19.
//

#include "co_symbol_table.h"
#include "../aul_utils.h"
#include <assert.h>
#include <string.h>

typedef struct symbol_table_entry {
	target_usize_t addr;
	const char* name;
	co_type_t type;
	uint64_t depth;
} symbol_table_entry;

typedef struct ts {
	symbol_table_entry table[TABLE_SIZE];
	uintptr_t index;
	uint64_t currDepth; // represents the current scope's depth
} ts;

ts* ts_make() {
	ts* result = malloc(sizeof(ts));
	result->index = 0;
	result->currDepth = 0;
	return result;
}

void ts_increase_depth(ts* table) {
	table->currDepth++;
}

void ts_decrease_depth(ts* table) {
	table->currDepth--;
	if((table->currDepth) < 0) {
		printf("An error occured ! \n");
	}
	// delete all variables with greater depth than the new one
	int cont = 1;
	for(uintptr_t i = table->index - 1; i >= 0 && (cont == 1); i--) {
		cont = 0;
		if(table->table[i].depth == ((table->currDepth) + 1)) {
			table->index--;
			cont = 1;
		}
	}
}

void ts_add(ts* ts, const char* name, co_type_t type, uint64_t depth) {
	symbol_table_entry entry;
	assert(name != NULL);
	entry.name = name;
	entry.type = type;
	entry.depth = ts->currDepth;
	if(ts->index == 0) {
		entry.addr = BASE_ADDR;
	} else {
		entry.addr = ts->table[ts->index - 1].addr + get_type_bytes_size(type);
	}
	ts->table[ts->index] = entry;
	ts->index++;
}

uint32_t ts_get(ts* ts, const char* name) {
	for(uintptr_t i = 0; i < ts->index; i++) {
		if(strcmp(ts->table[i].name, name) == 0) {
			return ts->table[i].addr;
		}
	}
	// Tried to get a symbol from an empty symbol table
	printf("ERROR : Can't find symbol %s\n", name);
	printf("Compilation failed\n");
	exit(1);
	return 0;
}

symbol_table_entry* last_entry(ts* ts) {
	return &ts->table[ts->index - 1];
}

void ts_pop_current_depth(ts* ts) {
	uint64_t current_depth = last_entry(ts)->depth;
	while(ts->table[ts->index - 1].depth == current_depth && ts->index > 0) {
		ts->index--;
	}
}

void ts_free(ts* ts) {
	free(ts);
}

uint32_t ts_gen_tmp(ts* ts) { // as temp variables don't have names we use _tmp to recognize them
	symbol_table_entry entry;
	entry.name = "_tmp";
	entry.depth = 6666666;
	entry.type = CONST;
	if(ts->index == 0) {
		entry.addr = BASE_ADDR;
	} else {
		entry.addr = ts->table[ts->index - 1].addr + sizeof(uint32_t);
	}
	ts->table[ts->index] = entry;
	ts->index++;
	return entry.addr;
}

uint32_t ts_pop_tmp(ts* ts) { // as temp variables don't have names we use _tmp to recognize them
	symbol_table_entry last_tmp = ts->table[ts->index - 1];
	// Error : Attempt to ts_pop_tmp a non temp variable
	assert(strcmp("_tmp", last_tmp.name) == 0); // a verifier ?
	ts->index--;
	return last_tmp.addr;
}