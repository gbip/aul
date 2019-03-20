//
// Created by paul on 20/03/19.
//

#include "symbol_table.h"

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

ts* make_ts() {
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
        entry.addr = base_addr;
    } else {
        entry.addr = ts->table[ts->index-1].addr + get_type_bytes_size(type);
    }
    ts->table[ts->index] = entry;
    ts->index++;
}

target_usize_t ts_get(ts* ts, const char* name) {
    return 0;
}

void step_out_of_block(ts* ts) {

}
