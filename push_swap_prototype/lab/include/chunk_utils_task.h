#ifndef CHUNK_UTILS_TASK_H
# define CHUNK_UTILS_TASK_H

#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Forward declarations for test structures
struct s_chunk_max_value_test;
typedef struct s_chunk_max_value_test t_chunk_max_value_test;
struct s_chunk_value_test;
typedef struct s_chunk_value_test t_chunk_value_test;
struct s_loc_to_stack_test;
typedef struct s_loc_to_stack_test t_loc_to_stack_test;

// Function to run loc_to_stack tests
int run_loc_to_stack_tests(int size);

// Function to run chunk_max_value tests
int run_chunk_max_value_tests(int size);

// Function to run chunk_value tests
int run_chunk_value_tests(int size);

#endif
