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
	
	// Create test batch with 4 test cases
    t_test_batch *batch = create_test_batch("chunk_max_value", 4);
    if (!batch) {
        printf("Failed to create test batch\n");
        cleanup_test_data(data);
        return 1;
    }
    
    // Copy chunk data for JSON export
    int *chunk_data = malloc(size * sizeof(int));
    if (!chunk_data) {
        printf("Failed to allocate chunk data\n");
        free_test_batch(batch);
        cleanup_test_data(data);
        return 1;
    }
    
    for (int i = 0; i < size; i++) {
        chunk_data[i] = data->a.stack[i];
    }
    
    // Test 1: Top A chunk max value
    int max_value_a = test_chunk_max_value_top_a(data);
    t_test_case *test1 = create_test_case(1, "TOP_A", chunk_data, size, max_value_a);
    set_test_param1(test1, "chunk_loc", "TOP_A");
    set_test_param2(test1, "chunk_size", 5);
    add_test_to_batch(batch, 0, test1);
    
    // Test 2: Bottom A chunk max value
    int max_value_b = test_chunk_max_value_bottom_a(data);
    t_test_case *test2 = create_test_case(2, "BOTTOM_A", chunk_data, size, max_value_b);
    set_test_param1(test2, "chunk_loc", "BOTTOM_A");
    set_test_param2(test2, "chunk_size", 4);
    add_test_to_batch(batch, 1, test2);
    
    // Test 3: Top B chunk max value
    int top_b_max = test_chunk_max_value_top_b(data);
    t_test_case *test3 = create_test_case(3, "TOP_B", chunk_data, size, top_b_max);
    set_test_param1(test3, "chunk_loc", "TOP_B");
    set_test_param2(test3, "chunk_size", 3);
    add_test_to_batch(batch, 2, test3);
    
    // Test 4: Bottom B chunk max value
    int bottom_b_max = test_chunk_max_value_bottom_b(data);
    t_test_case *test4 = create_test_case(4, "BOTTOM_B", chunk_data, size, bottom_b_max);
    set_test_param1(test4, "chunk_loc", "BOTTOM_B");
    set_test_param2(test4, "chunk_size", 3);
    add_test_to_batch(batch, 3, test4);
    
    // Save results to JSON file
    save_test_batch_to_json(batch, "chunk_max_value.json");
    
    // Cleanup
    free(chunk_data);
    free_test_batch(batch);
    cleanup_test_data(data);

    return 0;
}

// Function removed - now using generic t_test_batch approach directly
