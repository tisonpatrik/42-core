#ifndef CHUNK_SPLIT_TEST_H
# define CHUNK_SPLIT_TEST_H

#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Structure for chunk split test
typedef struct s_chunk_split_test {
    int id;
    char *name;
    int *input_array;
    int array_size;
    int original_chunk_size;
    char *original_chunk_loc;
    int min_size_result;
    int mid_size_result;
    int max_size_result;
    char *min_loc_result;
    char *mid_loc_result;
    char *max_loc_result;
} t_chunk_split_test;

// Function declarations
t_chunk_split_test* create_chunk_split_test(int id, const char *name, int *input_array, int array_size, 
                                           int original_chunk_size, const char *original_chunk_loc,
                                           int min_size_result, int mid_size_result, int max_size_result,
                                           const char *min_loc_result, const char *mid_loc_result, const char *max_loc_result);
void free_chunk_split_test(t_chunk_split_test *test);

#endif
