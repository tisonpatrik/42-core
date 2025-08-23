#ifndef CHUNK_VALUE_TEST_H
# define CHUNK_VALUE_TEST_H

#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Structure for chunk value test
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

// Function declarations
t_chunk_value_test* create_chunk_value_test(int id, const char *name, int *input_array, int array_size, int result, const char *chunk_loc, int chunk_size, int offset);
void free_chunk_value_test(t_chunk_value_test *test);

#endif
