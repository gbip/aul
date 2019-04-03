//
// Created by paul on 20/03/19.
//

#ifndef AUL_TYPES_H
#define AUL_TYPES_H

typedef enum co_type {
	INT,
	CONST,
} co_type_t;

int get_type_bytes_size(co_type_t type);

#endif // AUL_TYPES_H
