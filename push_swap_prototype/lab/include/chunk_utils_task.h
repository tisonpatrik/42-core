#ifndef CHUNK_UTILS_TASK_H
# define CHUNK_UTILS_TASK_H

#include "test_utils.h"
#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Generic test case structure
typedef struct s_test_case {
    int id;
    char *name;
    int *input_array;
    int array_size;
    int result;
    // Optional parameters for different test types
    char *param1_name;   // e.g., "stack_loc", "chunk_loc"
    char *param1_value;  // e.g., "TOP_A", "BOTTOM_B"
    char *param2_name;   // e.g., "chunk_size"
    int param2_value;    // e.g., 5, 4, 3
    char *param3_name;   // e.g., "offset"
    char *param3_value;  // e.g., "0 (start of chunk)"
} t_test_case;

// Generic test batch structure
typedef struct s_test_batch {
    t_test_case *tests;
    int num_tests;
    char *test_type;
} t_test_batch;

// Function to run loc_to_stack tests
int run_loc_to_stack_tests(int size);

// Function to run chunk_max_value tests
int run_chunk_max_value_tests(int size);

// Function to run chunk_value tests
int run_chunk_value_tests(int size);

// Test utility functions are declared in test_utils.h

#endif
