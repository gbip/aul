//
// Created by paul on 20/03/19.
//

#ifndef AUL_TYPES_H
#define AUL_TYPES_H


typedef enum type_t {
    INT,
    CONST,
} type_t;

int get_type_bytes_size(type_t type);

#endif //AUL_TYPES_H
