#include "../../../../include/chunk_split_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new chunk split test
t_chunk_split_test* create_chunk_split_test(int id, const char *name, int *input_array, int array_size, 
                                           int original_chunk_size, const char *original_chunk_loc,
                                           int min_size_result, int mid_size_result, int max_size_result,
                                           const char *min_loc_result, const char *mid_loc_result, const char *max_loc_result) {
    t_chunk_split_test *test = malloc(sizeof(t_chunk_split_test));
    if (!test) return NULL;
    
    test->id = id;
    test->name = strdup(name);
    test->array_size = array_size;
    test->original_chunk_size = original_chunk_size;
    test->original_chunk_loc = strdup(original_chunk_loc);
    test->min_size_result = min_size_result;
    test->mid_size_result = mid_size_result;
    test->max_size_result = max_size_result;
    test->min_loc_result = strdup(min_loc_result);
    test->mid_loc_result = strdup(mid_loc_result);
    test->max_loc_result = strdup(max_loc_result);
    
    // Allocate and copy input array
    test->input_array = malloc(array_size * sizeof(int));
    if (!test->input_array) {
        free(test->name);
        free(test->original_chunk_loc);
        free(test->min_loc_result);
        free(test->mid_loc_result);
        free(test->max_loc_result);
        free(test);
        return NULL;
    }
    memcpy(test->input_array, input_array, array_size * sizeof(int));
    
    return test;
}

// Free a chunk split test
void free_chunk_split_test(t_chunk_split_test *test) {
    if (!test) return;
    
    free(test->name);
    free(test->original_chunk_loc);
    free(test->min_loc_result);
    free(test->mid_loc_result);
    free(test->max_loc_result);
    free(test->input_array);
    free(test);
}
