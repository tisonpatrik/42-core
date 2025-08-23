#ifndef CHUNK_UTILS_TASK_H
# define CHUNK_UTILS_TASK_H

#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Specific structure for loc_to_stack test results
typedef struct s_loc_to_stack_test {
    int top_a_result;
    int bottom_a_result;
    int top_b_result;
    int bottom_b_result;
    int *stack_a_data;
    int stack_a_size;
    int *stack_b_data;
    int stack_b_size;
} t_loc_to_stack_test;

// Specific structure for chunk_max_value test results
typedef struct s_chunk_max_value_test {
    int max_value_a;
    int max_value_b;
    int max_value_combined;
    int *chunk_data;
    int chunk_size;
    int chunk_start_index;
    int chunk_end_index;
} t_chunk_max_value_test;

// Specific structure for chunk_value test results
typedef struct s_chunk_value_test {
    int target_value;
    int found_value;
    int found_index;
    int search_range_start;
    int search_range_end;
    int *search_data;
    int search_data_size;
    bool value_found;
} t_chunk_value_test;

// Function to run loc_to_stack tests
int run_loc_to_stack_tests(int size);

// Function to run chunk_max_value tests
int run_chunk_max_value_tests(int size);

// Function to run chunk_value tests
int run_chunk_value_tests(int size);

// Function to save loc_to_stack test results
void save_loc_to_stack_results(t_ps *data, t_loc_to_stack_test *test_data);

// Function to save chunk_max_value test results
void save_chunk_max_value_results(t_ps *data, t_chunk_max_value_test *test_data);

// Function to save chunk_value test results
void save_chunk_value_results(t_ps *data, t_chunk_value_test *test_data);

#endif
