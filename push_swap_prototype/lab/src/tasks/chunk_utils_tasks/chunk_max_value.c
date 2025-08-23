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
	
	// Run tests and collect results
    t_chunk_max_value_test test_data;
    
    // Test 1: Top A chunk max value
    test_data.max_value_a = test_chunk_max_value_top_a(data);
    
    // Test 2: Bottom A chunk max value
    test_data.max_value_b = test_chunk_max_value_bottom_a(data);
    
    // Test 3: Top B chunk max value
    int top_b_max = test_chunk_max_value_top_b(data);
    
    // Test 4: Bottom B chunk max value
    int bottom_b_max = test_chunk_max_value_bottom_b(data);
    
    // Find the overall maximum for combined result
    test_data.max_value_combined = test_data.max_value_a;
    if (test_data.max_value_b > test_data.max_value_combined)
        test_data.max_value_combined = test_data.max_value_b;
    if (top_b_max > test_data.max_value_combined)
        test_data.max_value_combined = top_b_max;
    if (bottom_b_max > test_data.max_value_combined)
        test_data.max_value_combined = bottom_b_max;
    
    // Copy chunk data for JSON export
    test_data.chunk_data = malloc(size * sizeof(int));
    test_data.chunk_size = size;
    if (test_data.chunk_data) {
        for (int i = 0; i < size; i++) {
            test_data.chunk_data[i] = data->a.stack[i];
        }
        test_data.chunk_start_index = 0;
        test_data.chunk_end_index = size - 1;
        
        // Save results to JSON file
        save_chunk_max_value_results(data, &test_data);
        
        // Cleanup test data
        free(test_data.chunk_data);
    }

    // Cleanup only once at the end
    cleanup_test_data(data);

    return 0;
}
