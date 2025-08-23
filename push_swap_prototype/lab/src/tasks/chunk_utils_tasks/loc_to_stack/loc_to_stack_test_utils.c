#include "../../../../include/testing/loc_to_stack_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new loc to stack test
t_loc_to_stack_test* create_loc_to_stack_test(int id, const char *name, int *input_array, int array_size, int result, const char *stack_loc) {
    t_loc_to_stack_test *test = malloc(sizeof(t_loc_to_stack_test));
    if (!test) return NULL;
    
    test->id = id;
    test->name = strdup(name);
    test->array_size = array_size;
    test->result = result;
    test->stack_loc = strdup(stack_loc);
    
    // Allocate and copy input array
    test->input_array = malloc(array_size * sizeof(int));
    if (!test->input_array) {
        free(test->name);
        free(test->stack_loc);
        free(test);
        return NULL;
    }
    memcpy(test->input_array, input_array, array_size * sizeof(int));
    
    return test;
}

// Free a loc to stack test
void free_loc_to_stack_test(t_loc_to_stack_test *test) {
    if (!test) return;
    
    free(test->name);
    free(test->stack_loc);
    free(test->input_array);
    free(test);
}
