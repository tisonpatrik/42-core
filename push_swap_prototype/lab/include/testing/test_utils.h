#ifndef TEST_UTILS_H
# define TEST_UTILS_H

#include "../core/types.h"
#include "test_config.h"

// Common test utility functions to eliminate duplication

// Stack data management
int* copy_stack_data(const int *source, int size);
void free_stack_data(int *data);

// Test resource management
void cleanup_test_resources(void **tests, int count);
t_ps* create_test_data_with_config(const t_test_config *config);

// Test case creation helpers
int create_test_cases_from_config(t_ps *data, const t_test_config *config, 
                                 void **tests, const char *test_type);

// Memory management
void safe_free(void *ptr);

#endif
