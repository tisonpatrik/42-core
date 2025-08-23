#ifndef CHUNK_UTILS_TESTS_H
# define CHUNK_UTILS_TESTS_H

#include "../core/types.h"

// Function declarations for chunk utility tests
// Each function is focused on a single testing responsibility

// Test loc_to_stack functionality
int run_loc_to_stack_tests(int size);

// Test chunk_max_value functionality  
int run_chunk_max_value_tests(int size);

// Test chunk_value functionality
int run_chunk_value_tests(int size);

#endif
