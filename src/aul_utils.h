//
// Created by paul on 21/03/19.
//

#ifndef AUL_UTILS_H
#define AUL_UTILS_H

#ifdef UNIT_TESTING
extern void* _test_malloc(const size_t size, const char* file, const int line);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
extern void* _test_free(void* ptr)
#define free(size) _test_free(ptr)
#else
#include "malloc.h"
#endif

#endif //AUL_UTILS_H
