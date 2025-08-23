#include "../../../libs/push_swap/src/models.h"
#include "../../../include/chunk_utils_task.h"
#include "../../../include/chunk_utils_common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Forward declaration of the function to test
t_stack	*loc_to_stack(t_ps *data, t_loc loc);

int	chunk_value(t_ps *data, t_chunk *chunk, int n);

// Test functions to return results instead of printing
int test_chunk_value_top_a_basic(t_ps *data) {
    t_chunk chunk = {TOP_A, 5};
    return chunk_value(data, &chunk, 0); // First element
}

int test_chunk_value_top_a_middle(t_ps *data) {
    t_chunk chunk = {TOP_A, 5};
    return chunk_value(data, &chunk, 2); // Third element
}

int test_chunk_value_bottom_b_basic(t_ps *data) {
    t_chunk chunk = {BOTTOM_B, 4};
    return chunk_value(data, &chunk, 0); // Bottom element
}

int test_chunk_value_bottom_b_second(t_ps *data) {
    t_chunk chunk = {BOTTOM_B, 4};
    return chunk_value(data, &chunk, 1); // Second from bottom
}

int test_chunk_value_top_b_last(t_ps *data) {
    t_chunk chunk = {TOP_B, 3};
    return chunk_value(data, &chunk, 2); // Last element in chunk
}

// Main function to run chunk_value tests
int run_chunk_value_tests(int size) {
	t_ps *data = create_test_data(size, size);
	if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
	
	// Initialize test data structure
    t_chunk_value_test test_data = {0};
    
    // Test 1: TOP_A, size=5, offset=0 (first element in chunk)
    test_data.test1_top_a_basic.input_array = malloc(size * sizeof(int));
    test_data.test1_top_a_basic.array_size = size;
    test_data.test1_top_a_basic.chunk_loc = TOP_A;
    test_data.test1_top_a_basic.chunk_size = 5;
    test_data.test1_top_a_basic.offset = 0;  // Start at beginning of chunk
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test1_top_a_basic.input_array[i] = data->a.stack[i];
    }
    
    // Run test
    t_chunk chunk1 = {TOP_A, 5};
    test_data.test1_top_a_basic.result = chunk_value(data, &chunk1, 0);
    
    // Test 2: TOP_A, size=5, offset=2 (third element in chunk)
    test_data.test2_top_a_middle.input_array = malloc(size * sizeof(int));
    test_data.test2_top_a_middle.array_size = size;
    test_data.test2_top_a_middle.chunk_loc = TOP_A;
    test_data.test2_top_a_middle.chunk_size = 5;
    test_data.test2_top_a_middle.offset = 2;  // Move 2 steps from start of chunk
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test2_top_a_middle.input_array[i] = data->a.stack[i];
    }
    
    // Run test
    t_chunk chunk2 = {TOP_A, 5};
    test_data.test2_top_a_middle.result = chunk_value(data, &chunk2, 2);
    
    // Test 3: BOTTOM_B, size=4, offset=0 (first element in chunk)
    test_data.test3_bottom_b_basic.input_array = malloc(size * sizeof(int));
    test_data.test3_bottom_b_basic.array_size = size;
    test_data.test3_bottom_b_basic.chunk_loc = BOTTOM_B;
    test_data.test3_bottom_b_basic.chunk_size = 4;
    test_data.test3_bottom_b_basic.offset = 0;  // Start at beginning of chunk
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test3_bottom_b_basic.input_array[i] = data->b.stack[i];
    }
    
    // Run test
    t_chunk chunk3 = {BOTTOM_B, 4};
    test_data.test3_bottom_b_basic.result = chunk_value(data, &chunk3, 0);
    
    // Test 4: BOTTOM_B, size=4, offset=1 (second element in chunk)
    test_data.test4_bottom_b_second.input_array = malloc(size * sizeof(int));
    test_data.test4_bottom_b_second.array_size = size;
    test_data.test4_bottom_b_second.chunk_loc = BOTTOM_B;
    test_data.test4_bottom_b_second.chunk_size = 4;
    test_data.test4_bottom_b_second.offset = 1;  // Move 1 step from start of chunk
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test4_bottom_b_second.input_array[i] = data->b.stack[i];
    }
    
    // Run test
    t_chunk chunk4 = {BOTTOM_B, 4};
    test_data.test4_bottom_b_second.result = chunk_value(data, &chunk4, 1);
    
    // Test 5: TOP_B, size=3, offset=2 (third element in chunk)
    test_data.test5_top_b_last.input_array = malloc(size * sizeof(int));
    test_data.test5_top_b_last.array_size = size;
    test_data.test5_top_b_last.chunk_loc = TOP_B;
    test_data.test5_top_b_last.chunk_size = 3;
    test_data.test5_top_b_last.offset = 2;  // Move 2 steps from start of chunk
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test5_top_b_last.input_array[i] = data->b.stack[i];
    }
    
    // Run test
    t_chunk chunk5 = {TOP_B, 3};
    test_data.test5_top_b_last.result = chunk_value(data, &chunk5, 2);
    
    // Save results to JSON file
    save_chunk_value_results(data, &test_data);
    
    // Cleanup test data
    free(test_data.test1_top_a_basic.input_array);
    free(test_data.test2_top_a_middle.input_array);
    free(test_data.test3_bottom_b_basic.input_array);
    free(test_data.test4_bottom_b_second.input_array);
    free(test_data.test5_top_b_last.input_array);

    // Cleanup only once at the end
    cleanup_test_data(data);

    return 0;
}


