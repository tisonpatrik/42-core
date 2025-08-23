#include "../../../libs/push_swap/src/models.h"
#include "../../../include/chunk_utils_task.h"
#include "../../../include/chunk_utils_common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Forward declaration of the function to test
t_stack	*loc_to_stack(t_ps *data, t_loc loc);

int	chunk_max_value(t_ps *data, t_chunk *chunk);

// Test functions to return results instead of printing
int test_chunk_max_value_top_a(t_ps *data) {
    t_chunk chunk = {TOP_A, 5};
    return chunk_max_value(data, &chunk);
}

int test_chunk_max_value_bottom_a(t_ps *data) {
    t_chunk chunk = {BOTTOM_A, 4};
    return chunk_max_value(data, &chunk);
}

int test_chunk_max_value_top_b(t_ps *data) {
    t_chunk chunk = {TOP_B, 3};
    return chunk_max_value(data, &chunk);
}

int test_chunk_max_value_bottom_b(t_ps *data) {
    t_chunk chunk = {BOTTOM_B, 4};
    return chunk_max_value(data, &chunk);
}

// Main function to run chunk_max_value tests
int run_chunk_max_value_tests(int size) {
	t_ps *data = create_test_data(size, size);
	if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
	
	// Initialize test data structure
    t_chunk_max_value_test test_data = {0};
    
    // Test 1: TOP_A, size=5
    test_data.test1_top_a.input_array = malloc(size * sizeof(int));
    test_data.test1_top_a.array_size = size;
    test_data.test1_top_a.chunk_loc = TOP_A;
    test_data.test1_top_a.chunk_size = 5;
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test1_top_a.input_array[i] = data->a.stack[i];
    }
    
    // Run test
    t_chunk chunk1 = {TOP_A, 5};
    test_data.test1_top_a.result = chunk_max_value(data, &chunk1);
    
    // Test 2: BOTTOM_A, size=4
    test_data.test2_bottom_a.input_array = malloc(size * sizeof(int));
    test_data.test2_bottom_a.array_size = size;
    test_data.test2_bottom_a.chunk_loc = BOTTOM_A;
    test_data.test2_bottom_a.chunk_size = 4;
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test2_bottom_a.input_array[i] = data->a.stack[i];
    }
    
    // Run test
    t_chunk chunk2 = {BOTTOM_A, 4};
    test_data.test2_bottom_a.result = chunk_max_value(data, &chunk2);
    
    // Test 3: TOP_B, size=3
    test_data.test3_top_b.input_array = malloc(size * sizeof(int));
    test_data.test3_top_b.array_size = size;
    test_data.test3_top_b.chunk_loc = TOP_B;
    test_data.test3_top_b.chunk_size = 3;
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test3_top_b.input_array[i] = data->b.stack[i];
    }
    
    // Run test
    t_chunk chunk3 = {TOP_B, 3};
    test_data.test3_top_b.result = chunk_max_value(data, &chunk3);
    
    // Test 4: BOTTOM_B, size=4
    test_data.test4_bottom_b.input_array = malloc(size * sizeof(int));
    test_data.test4_bottom_b.array_size = size;
    test_data.test4_bottom_b.chunk_loc = BOTTOM_B;
    test_data.test4_bottom_b.chunk_size = 4;
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test4_bottom_b.input_array[i] = data->b.stack[i];
    }
    
    // Run test
    t_chunk chunk4 = {BOTTOM_B, 4};
    test_data.test4_bottom_b.result = chunk_max_value(data, &chunk4);
    
    // Save results to JSON file
    save_chunk_max_value_results(data, &test_data);
    
    // Cleanup test data
    free(test_data.test1_top_a.input_array);
    free(test_data.test2_bottom_a.input_array);
    free(test_data.test3_top_b.input_array);
    free(test_data.test4_bottom_b.input_array);

    // Cleanup only once at the end
    cleanup_test_data(data);

    return 0;
}
