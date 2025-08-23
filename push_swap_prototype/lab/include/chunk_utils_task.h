#ifndef CHUNK_UTILS_TASK_H
# define CHUNK_UTILS_TASK_H

#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Chunk max value test structure
typedef struct s_chunk_max_value_test {
    int id;
    char *name;
    int *input_array;
    int array_size;
    int result;
    char *chunk_loc;     // e.g., "TOP_A", "BOTTOM_B"
    int chunk_size;      // e.g., 5, 4, 3
} t_chunk_max_value_test;

// Chunk value test structure
typedef struct s_chunk_value_test {
    int id;
    char *name;
    int *input_array;
    int array_size;
    int result;
    char *chunk_loc;     // e.g., "TOP_A", "BOTTOM_B"
    int chunk_size;      // e.g., 5, 4, 3
    int offset;          // Position within chunk
} t_chunk_value_test;

// Loc to stack test structure
typedef struct s_loc_to_stack_test {
    int id;
    char *name;
    int *input_array;
    int array_size;
    int result;
    char *stack_loc;     // e.g., "TOP_A", "BOTTOM_B"
} t_loc_to_stack_test;

// Function to run loc_to_stack tests
int run_loc_to_stack_tests(int size);

// Function to run chunk_max_value tests
int run_chunk_max_value_tests(int size);

// Function to run chunk_value tests
int run_chunk_value_tests(int size);

#endif
