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

// Business logic function to save chunk_max_value test results
void save_chunk_max_value_results(t_ps *data __attribute__((unused)), t_chunk_max_value_test *test_data) {
    if (!test_data) return;
    
    // Create test batch
    t_test_batch *batch = create_test_batch("chunk_max_value", 4);
    if (!batch) return;
    
    // Create test cases using the clean utility functions
    t_test_case test1 = {0};
    test1.id = 1;
    test1.name = "TOP_A";
    test1.input_array = test_data->chunk_data;
    test1.array_size = test_data->chunk_size;
    test1.result = test_data->max_value_a;
    test1.param1_name = "chunk_loc";
    test1.param1_value = "TOP_A";
    test1.param2_name = "chunk_size";
    test1.param2_value = 5;
    
    t_test_case test2 = {0};
    test2.id = 2;
    test2.name = "BOTTOM_A";
    test2.input_array = test_data->chunk_data;
    test2.array_size = test_data->chunk_size;
    test2.result = test_data->max_value_b;
    test2.param1_name = "chunk_loc";
    test2.param1_value = "BOTTOM_A";
    test2.param2_name = "chunk_size";
    test2.param2_value = 4;
    
    t_test_case test3 = {0};
    test3.id = 3;
    test3.name = "TOP_B";
    test3.input_array = test_data->chunk_data;
    test3.array_size = test_data->chunk_size;
    test3.result = test_data->max_value_combined;
    test3.param1_name = "chunk_loc";
    test3.param1_value = "TOP_B";
    test3.param2_name = "chunk_size";
    test3.param2_value = 3;
    
    t_test_case test4 = {0};
    test4.id = 4;
    test4.name = "BOTTOM_B";
    test4.input_array = test_data->chunk_data;
    test4.array_size = test_data->chunk_size;
    test4.result = test_data->max_value_combined;
    test4.param1_name = "chunk_loc";
    test4.param1_value = "BOTTOM_B";
    test4.param2_name = "chunk_size";
    test4.param2_value = 4;
    
    // Add tests to batch
    add_test_to_batch(batch, 0, &test1);
    add_test_to_batch(batch, 1, &test2);
    add_test_to_batch(batch, 2, &test3);
    add_test_to_batch(batch, 3, &test4);
    
    // Save to file using the clean utility function
    save_test_batch_to_json(batch, "chunk_max_value.json");
    
    // Cleanup
    free_test_batch(batch);
}
