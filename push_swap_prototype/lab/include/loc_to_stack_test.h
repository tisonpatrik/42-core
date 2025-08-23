#ifndef LOC_TO_STACK_TEST_H
# define LOC_TO_STACK_TEST_H

#include <stdbool.h>

// Forward declaration - models.h is already included in the .c file
struct s_push_swap;
typedef struct s_push_swap t_ps;

// Structure for loc to stack test
typedef struct s_loc_to_stack_test {
    int id;
    char *name;
    int *input_array;
    int array_size;
    int result;
    char *stack_loc;
} t_loc_to_stack_test;

// Function declarations
t_loc_to_stack_test* create_loc_to_stack_test(int id, const char *name, int *input_array, int array_size, int result, const char *stack_loc);
void free_loc_to_stack_test(t_loc_to_stack_test *test);

#endif
