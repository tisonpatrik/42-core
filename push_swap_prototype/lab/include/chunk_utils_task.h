#ifndef CHUNK_UTILS_TASK_H
# define CHUNK_UTILS_TASK_H

#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Specific structure for loc_to_stack test results
typedef struct s_loc_to_stack_test {
    // Test 1: TOP_A
    struct {
        int *input_array;
        int array_size;
        int stack_loc;
        int result;
    } test1_top_a;
    
    // Test 2: BOTTOM_A
    struct {
        int *input_array;
        int array_size;
        int stack_loc;
        int result;
    } test2_bottom_a;
    
    // Test 3: TOP_B
    struct {
        int *input_array;
        int array_size;
        int stack_loc;
        int result;
    } test3_top_b;
    
    // Test 4: BOTTOM_B
    struct {
        int *input_array;
        int array_size;
        int stack_loc;
        int result;
    } test4_bottom_b;
} t_loc_to_stack_test;

// Specific structure for chunk_max_value test results
typedef struct s_chunk_max_value_test {
    // Test 1: TOP_A, size=5
    struct {
        int *input_array;
        int array_size;
        int chunk_loc;
        int chunk_size;
        int result;
    } test1_top_a;
    
    // Test 2: BOTTOM_A, size=4
    struct {
        int *input_array;
        int array_size;
        int chunk_loc;
        int chunk_size;
        int result;
    } test2_bottom_a;
    
    // Test 3: TOP_B, size=3
    struct {
        int *input_array;
        int array_size;
        int chunk_loc;
        int chunk_size;
        int result;
    } test3_top_b;
    
    // Test 4: BOTTOM_B, size=4
    struct {
        int *input_array;
        int array_size;
        int chunk_loc;
        int chunk_size;
        int result;
    } test4_bottom_b;
} t_chunk_max_value_test;

// Specific structure for chunk_value test results
typedef struct s_chunk_value_test {
    // Test 1: TOP_A, size=5, offset=0
    struct {
        int *input_array;
        int array_size;
        int chunk_loc;
        int chunk_size;
        int offset;
        int result;
    } test1_top_a_basic;
    
    // Test 2: TOP_A, size=5, offset=2
    struct {
        int *input_array;
        int array_size;
        int chunk_loc;
        int chunk_size;
        int offset;
        int result;
    } test2_top_a_middle;
    
    // Test 3: BOTTOM_B, size=4, offset=0
    struct {
        int *input_array;
        int array_size;
        int chunk_loc;
        int chunk_size;
        int offset;
        int result;
    } test3_bottom_b_basic;
    
    // Test 4: BOTTOM_B, size=4, offset=1
    struct {
        int *input_array;
        int array_size;
        int chunk_loc;
        int chunk_size;
        int offset;
        int result;
    } test4_bottom_b_second;
    
    // Test 5: TOP_B, size=3, offset=2
    struct {
        int *input_array;
        int array_size;
        int chunk_loc;
        int chunk_size;
        int offset;
        int result;
    } test5_top_b_last;
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
