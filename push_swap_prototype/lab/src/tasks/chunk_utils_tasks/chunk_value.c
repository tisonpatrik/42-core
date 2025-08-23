#include "../../../include/chunk_utils_task.h"
#include "../../../include/json_utils.h"
#include "../../../include/stack_utils.h"
#include "../../../include/test_utils.h"
#include "../../../libs/push_swap/src/chunk_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Functions are implemented in libs/push_swap/src/chunk_utils.c

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
	
	// Create test batch with 5 test cases
    t_test_batch *batch = create_test_batch("chunk_value", 5);
    if (!batch) {
        printf("Failed to create test batch\n");
        cleanup_test_data(data);
        return 1;
    }
    
    // Test 1: TOP_A, size=5, offset=0 (first element in chunk)
    int *input_array1 = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        input_array1[i] = data->a.stack[i];
    }
    
    t_chunk chunk1 = {TOP_A, 5};
    int result1 = chunk_value(data, &chunk1, 0);
    
    t_test_case *test1 = create_test_case(1, "TOP_A_basic", input_array1, size, result1);
    set_test_param1(test1, "chunk_loc", "TOP_A");
    set_test_param2(test1, "chunk_size", 5);
    set_test_param3(test1, "offset", "0");
    add_test_to_batch(batch, 0, test1);
    
    // Test 2: TOP_A, size=5, offset=2 (third element in chunk)
    int *input_array2 = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        input_array2[i] = data->a.stack[i];
    }
    
    t_chunk chunk2 = {TOP_A, 5};
    int result2 = chunk_value(data, &chunk2, 2);
    
    t_test_case *test2 = create_test_case(2, "TOP_A_middle", input_array2, size, result2);
    set_test_param1(test1, "chunk_loc", "TOP_A");
    set_test_param2(test1, "chunk_size", 5);
    set_test_param3(test1, "offset", "2");
    add_test_to_batch(batch, 1, test2);
    
    // Test 3: BOTTOM_B, size=4, offset=0 (first element in chunk)
    int *input_array3 = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        input_array3[i] = data->b.stack[i];
    }
    
    t_chunk chunk3 = {BOTTOM_B, 4};
    int result3 = chunk_value(data, &chunk3, 0);
    
    t_test_case *test3 = create_test_case(3, "BOTTOM_B_basic", input_array3, size, result3);
    set_test_param1(test1, "chunk_loc", "BOTTOM_B");
    set_test_param2(test1, "chunk_size", 4);
    set_test_param3(test1, "offset", "0");
    add_test_to_batch(batch, 2, test3);
    
    // Test 4: BOTTOM_B, size=4, offset=1 (second element in chunk)
    int *input_array4 = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        input_array4[i] = data->b.stack[i];
    }
    
    t_chunk chunk4 = {BOTTOM_B, 4};
    int result4 = chunk_value(data, &chunk4, 1);
    
    t_test_case *test4 = create_test_case(4, "BOTTOM_B_second", input_array4, size, result4);
    set_test_param1(test1, "chunk_loc", "BOTTOM_B");
    set_test_param2(test1, "chunk_size", 4);
    set_test_param3(test1, "offset", "1");
    add_test_to_batch(batch, 3, test4);
    
    // Test 5: TOP_B, size=3, offset=2 (third element in chunk)
    int *input_array5 = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        input_array5[i] = data->b.stack[i];
    }
    
    t_chunk chunk5 = {TOP_B, 3};
    int result5 = chunk_value(data, &chunk5, 2);
    
    t_test_case *test5 = create_test_case(5, "TOP_B_last", input_array5, size, result5);
    set_test_param1(test1, "chunk_loc", "TOP_B");
    set_test_param2(test1, "chunk_size", 3);
    set_test_param3(test1, "offset", "2");
    add_test_to_batch(batch, 4, test5);
    
    // Save results to JSON file
    save_test_batch_to_json(batch, "chunk_value.json");
    
    // Cleanup
    free_test_batch(batch);
    cleanup_test_data(data);
    
    return 0;
}

// Function removed - now using generic t_test_batch approach directly


