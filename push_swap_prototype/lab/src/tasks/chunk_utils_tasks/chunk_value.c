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

// Business logic function to save chunk_value test results
void save_chunk_value_results(t_ps *data __attribute__((unused)), t_chunk_value_test *test_data) {
    if (!test_data) return;
    
    // Create test batch
    t_test_batch *batch = create_test_batch("chunk_value", 5);
    if (!batch) return;
    
    // Create test cases using the clean utility functions
    t_test_case test1 = {0};
    test1.id = 1;
    test1.name = "TOP_A_BASIC";
    test1.input_array = test_data->test1_top_a_basic.input_array;
    test1.array_size = test_data->test1_top_a_basic.array_size;
    test1.result = test_data->test1_top_a_basic.result;
    test1.param1_name = "chunk_loc";
    test1.param1_value = "TOP_A";
    test1.param2_name = "chunk_size";
    test1.param2_value = 5;
    test1.param3_name = "offset";
    test1.param3_value = "0 (start of chunk)";
    
    t_test_case test2 = {0};
    test2.id = 2;
    test2.name = "TOP_A_MIDDLE";
    test2.input_array = test_data->test2_top_a_middle.input_array;
    test2.array_size = test_data->test2_top_a_middle.array_size;
    test2.result = test_data->test2_top_a_middle.result;
    test2.param1_name = "chunk_loc";
    test2.param1_value = "TOP_A";
    test2.param2_name = "chunk_size";
    test2.param2_value = 5;
    test2.param3_name = "offset";
    test2.param3_value = "2 (third element in chunk)";
    
    t_test_case test3 = {0};
    test3.id = 3;
    test3.name = "BOTTOM_B_BASIC";
    test3.input_array = test_data->test3_bottom_b_basic.input_array;
    test3.array_size = test_data->test3_bottom_b_basic.array_size;
    test3.result = test_data->test3_bottom_b_basic.result;
    test3.param1_name = "chunk_loc";
    test3.param1_value = "BOTTOM_B";
    test3.param2_name = "chunk_size";
    test3.param2_value = 4;
    test3.param3_name = "offset";
    test3.param3_value = "0 (start of chunk)";
    
    t_test_case test4 = {0};
    test4.id = 4;
    test4.name = "BOTTOM_B_SECOND";
    test4.input_array = test_data->test4_bottom_b_second.input_array;
    test4.array_size = test_data->test4_bottom_b_second.array_size;
    test4.result = test_data->test4_bottom_b_second.result;
    test4.param1_name = "chunk_loc";
    test4.param1_value = "BOTTOM_B";
    test4.param2_name = "chunk_size";
    test4.param2_value = 4;
    test4.param3_name = "offset";
    test4.param3_value = "1 (second element in chunk)";
    
    t_test_case test5 = {0};
    test5.id = 5;
    test5.name = "TOP_B_LAST";
    test5.input_array = test_data->test5_top_b_last.input_array;
    test5.array_size = test_data->test5_top_b_last.array_size;
    test5.result = test_data->test5_top_b_last.result;
    test5.param1_name = "chunk_loc";
    test5.param1_value = "TOP_B";
    test5.param2_name = "chunk_size";
    test5.param2_value = 3;
    test5.param3_name = "offset";
    test5.param3_value = "2 (third element in chunk)";
    
    // Add tests to batch
    add_test_to_batch(batch, 0, &test1);
    add_test_to_batch(batch, 1, &test2);
    add_test_to_batch(batch, 2, &test3);
    add_test_to_batch(batch, 3, &test4);
    add_test_to_batch(batch, 4, &test5);
    
    // Save to file using the clean utility function
    save_test_batch_to_json(batch, "chunk_value.json");
    
    // Cleanup
    free_test_batch(batch);
}


