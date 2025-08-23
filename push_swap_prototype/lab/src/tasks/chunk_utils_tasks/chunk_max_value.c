#include "../../../include/chunk_utils_task.h"
#include "../../../include/specific_test_utils.h"
#include "../../../include/specific_json_utils.h"
#include "../../../include/stack_utils.h"
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
	
	// Create array of 4 test cases
    t_chunk_max_value_test *tests[4] = {NULL};
    
    // Copy chunk data for JSON export
    int *chunk_data = malloc(size * sizeof(int));
    if (!chunk_data) {
        printf("Failed to allocate chunk data\n");
        cleanup_test_data(data);
        return 1;
    }
    
    for (int i = 0; i < size; i++) {
        chunk_data[i] = data->a.stack[i];
    }
    
    // Test 1: Top A chunk max value
    int max_value_a = test_chunk_max_value_top_a(data);
    tests[0] = create_chunk_max_value_test(1, "TOP_A", chunk_data, size, max_value_a, "TOP_A", 5);
    
    // Test 2: Bottom A chunk max value
    int max_value_b = test_chunk_max_value_bottom_a(data);
    tests[1] = create_chunk_max_value_test(2, "BOTTOM_A", chunk_data, size, max_value_b, "BOTTOM_A", 4);
    
    // Test 3: Top B chunk max value
    int top_b_max = test_chunk_max_value_top_b(data);
    tests[2] = create_chunk_max_value_test(3, "TOP_B", chunk_data, size, top_b_max, "TOP_B", 3);
    
    // Test 4: Bottom B chunk max value
    int bottom_b_max = test_chunk_max_value_bottom_b(data);
    tests[3] = create_chunk_max_value_test(4, "BOTTOM_B", chunk_data, size, bottom_b_max, "BOTTOM_B", 4);
    
    // Save results to JSON file
    save_chunk_max_value_tests_to_json(tests, 4, "chunk_max_value.json");
    
    // Cleanup
    free(chunk_data);
    for (int i = 0; i < 4; i++) {
        if (tests[i]) {
            free_chunk_max_value_test(tests[i]);
        }
    }
    cleanup_test_data(data);

    return 0;
}
