//
// Created by paul on 20/03/19.
//

#include <string.h>
#include "co_symbol_table.h"

typedef struct symbol_table_entry {
    target_usize_t addr;
    const char* name;
    type_t type;
    uint64_t depth;
} symbol_table_entry;

typedef struct ts {
    symbol_table_entry table[TABLE_SIZE];
    uintptr_t index;
} ts;

ts* ts_make() {
    ts* result = malloc(sizeof(ts));
    result->index = 0;
    return result;
}

void ts_add(ts* ts, const char* name, type_t type, uint64_t depth) {
    symbol_table_entry entry;
    entry.name = name;
    entry.type = type;
    entry.depth = depth;
    if (ts-> index == 0) {
        entry.addr = BASE_ADDR;
    } else {
        entry.addr = ts->table[ts->index-1].addr + get_type_bytes_size(type);
    }
    ts->table[ts->index] = entry;
    ts->index++;
}

target_usize_t* ts_get(ts* ts, const char* name) {
    for (uintptr_t i = 0; i < ts->index; i++) {
        if (strcmp(ts->table[i].name, name) == 0) {
            return &ts->table[i].addr;
        }
    }
    return NULL;
}

symbol_table_entry* last_entry(ts* ts) {
    return &ts->table[ts->index];
}

void ts_pop_current_depth(ts *ts) {
    uint64_t current_depth = last_entry(ts)->depth;
    while (ts->table[ts->index].depth == current_depth && ts->index > 0) {
        ts->index--;
    }
}

void ts_free(ts *ts) {
    free(ts);
}