#ifndef FUNC_H
#define FUNC_H

#include <stddef.h>

typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = 1,
    ERROR_INVALID_INPUT = 2,
    ERROR_MEMORY_ALLOCATION = 3
} StatusCode;

StatusCode obrez(const char* input, char** result, char* remaining);
StatusCode add_probel(char** string, size_t target_length);
int is_readable_char(char c);

#endif
