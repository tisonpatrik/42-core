#ifndef LOC_TO_STACK_TEST_H
# define LOC_TO_STACK_TEST_H

#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Loc to stack test structure
typedef struct s_loc_to_stack_test {
    int id;
    char *name;
    int *input_array;
    int array_size;
    int result;
    char *stack_loc;     // e.g., "TOP_A", "BOTTOM_B"
} t_loc_to_stack_test;

// Test utility functions
t_loc_to_stack_test* create_loc_to_stack_test(int id, const char *name, int *input_array, int array_size, int result, const char *stack_loc);
void free_loc_to_stack_test(t_loc_to_stack_test *test);

// JSON export function
void save_loc_to_stack_tests_to_json(t_loc_to_stack_test **tests, int num_tests, const char *filename);

// Main test runner
int run_loc_to_stack_tests(int size);

#endif
