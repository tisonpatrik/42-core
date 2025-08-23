#ifndef CHUNK_VALUE_TEST_H
# define CHUNK_VALUE_TEST_H

#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

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

// Test utility functions
t_chunk_value_test* create_chunk_value_test(int id, const char *name, int *input_array, int array_size, int result, const char *chunk_loc, int chunk_size, int offset);
void free_chunk_value_test(t_chunk_value_test *test);

// JSON export function
void save_chunk_value_tests_to_json(t_chunk_value_test **tests, int num_tests, const char *filename);

// Main test runner
int run_chunk_value_tests(int size);

#endif
