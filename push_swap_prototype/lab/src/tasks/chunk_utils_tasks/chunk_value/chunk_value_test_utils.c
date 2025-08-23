#include "../../../../include/chunk_value_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new chunk value test
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
    
    // Allocate and copy input array
    test->input_array = malloc(array_size * sizeof(int));
    if (!test->input_array) {
        free(test->name);
        free(test->chunk_loc);
        free(test);
        return NULL;
    }
    memcpy(test->input_array, input_array, array_size * sizeof(int));
    
    return test;
}

// Free a chunk value test
void free_chunk_value_test(t_chunk_value_test *test) {
    if (!test) return;
    
    free(test->name);
    free(test->chunk_loc);
    free(test->input_array);
    free(test);
}
