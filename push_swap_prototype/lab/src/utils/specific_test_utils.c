#include "../../include/chunk_utils_task.h"
#include <stdlib.h>
#include <string.h>

// Chunk max value test utilities
t_chunk_max_value_test* create_chunk_max_value_test(int id, const char *name, int *input_array, int array_size, int result, const char *chunk_loc, int chunk_size) {
    t_chunk_max_value_test *test = malloc(sizeof(t_chunk_max_value_test));
    if (!test) return NULL;
    
    test->id = id;
    test->name = strdup(name);
    test->array_size = array_size;
    test->result = result;
    test->chunk_loc = strdup(chunk_loc);
    test->chunk_size = chunk_size;
    
    // Copy input array
    if (input_array && array_size > 0) {
        test->input_array = malloc(array_size * sizeof(int));
        if (test->input_array) {
            for (int i = 0; i < array_size; i++) {
                test->input_array[i] = input_array[i];
            }
        }
    } else {
        test->input_array = NULL;
    }
    
    return test;
}

void free_chunk_max_value_test(t_chunk_max_value_test *test) {
    if (test) {
        if (test->name) free(test->name);
        if (test->input_array) free(test->input_array);
        if (test->chunk_loc) free(test->chunk_loc);
        free(test);
    }
}

// Chunk value test utilities
t_chunk_value_test* create_chunk_value_test(int id, const char *name, int *input_array, int array_size, int result, const char *chunk_loc, int chunk_size, int offset) {
    t_chunk_value_test *test = malloc(sizeof(t_chunk_value_test));
    if (!test) return NULL;
    
    test->id = id;
    test->name = strdup(name);
    test->array_size = array_size;
    test->result = result;
    test->chunk_loc = strdup(chunk_loc);
    test->chunk_size = chunk_size;
    test->offset = offset;
    
    // Copy input array
    if (input_array && array_size > 0) {
        test->input_array = malloc(array_size * sizeof(int));
        if (test->input_array) {
            for (int i = 0; i < array_size; i++) {
                test->input_array[i] = input_array[i];
            }
        }
    } else {
        test->input_array = NULL;
    }
    
    return test;
}

void free_chunk_value_test(t_chunk_value_test *test) {
    if (test) {
        if (test->name) free(test->name);
        if (test->input_array) free(test->input_array);
        if (test->chunk_loc) free(test->chunk_loc);
        free(test);
    }
}

// Loc to stack test utilities
t_loc_to_stack_test* create_loc_to_stack_test(int id, const char *name, int *input_array, int array_size, int result, const char *stack_loc) {
    t_loc_to_stack_test *test = malloc(sizeof(t_loc_to_stack_test));
    if (!test) return NULL;
    
    test->id = id;
    test->name = strdup(name);
    test->array_size = array_size;
    test->result = result;
    test->stack_loc = strdup(stack_loc);
    
    // Copy input array
    if (input_array && array_size > 0) {
        test->input_array = malloc(array_size * sizeof(int));
        if (test->input_array) {
            for (int i = 0; i < array_size; i++) {
                test->input_array[i] = input_array[i];
            }
        }
    } else {
        test->input_array = NULL;
    }
    
    return test;
}

void free_loc_to_stack_test(t_loc_to_stack_test *test) {
    if (test) {
        if (test->name) free(test->name);
        if (test->input_array) free(test->input_array);
        if (test->stack_loc) free(test->stack_loc);
        free(test);
    }
}
