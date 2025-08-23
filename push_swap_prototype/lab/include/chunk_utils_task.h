#ifndef CHUNK_UTILS_TASK_H
# define CHUNK_UTILS_TASK_H

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

// Generic helper functions
t_test_case* create_test_case(int id, const char *name, int *input_array, int array_size, int result);
void set_test_param1(t_test_case *test, const char *name, const char *value);
void set_test_param2(t_test_case *test, const char *name, int value);
void set_test_param3(t_test_case *test, const char *name, const char *value);
void free_test_case(t_test_case *test);

t_test_batch* create_test_batch(const char *test_type, int num_tests);
void add_test_to_batch(t_test_batch *batch, int index, t_test_case *test);
void free_test_batch(t_test_batch *batch);

// Generic JSON export function
void save_test_batch_to_json(t_test_batch *batch, const char *filename);

#endif
