#ifndef JSON_UTILS_H
# define JSON_UTILS_H

#include <stddef.h>
#include "error_utils.h"

// Generic function to save any test array to JSON
// Uses callback function to add test-specific data
int save_tests_to_json_generic(const char *filename, const char *test_type, 
                               void **tests, int num_tests, 
                               void (*add_test_data)(void *test_obj, void *test));

// Helper function to add input array to JSON
void add_input_array_to_json(void *test_obj, int *input_array, int array_size);

// Callback functions for specific test types
void add_chunk_value_test_data(void *test_obj, void *test);
void add_chunk_max_value_test_data(void *test_obj, void *test);
void add_loc_to_stack_test_data(void *test_obj, void *test);

#endif
