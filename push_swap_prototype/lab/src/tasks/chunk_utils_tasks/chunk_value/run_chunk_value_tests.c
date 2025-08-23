#include "../../../../include/chunk_value_test.h"
#include "../../../../include/stack_utils.h"
#include "../../../../libs/push_swap/src/chunk_utils.h"
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
	
	// Create array of 5 test cases
    t_chunk_value_test *tests[5] = {NULL};
    
    // Test 1: TOP_A, size=5, offset=0 (first element in chunk)
    int *input_array1 = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        input_array1[i] = data->a.stack[i];
    }
    
    t_chunk chunk1 = {TOP_A, 5};
    int result1 = chunk_value(data, &chunk1, 0);
    
    tests[0] = create_chunk_value_test(1, "TOP_A_basic", input_array1, size, result1, "TOP_A", 5, 0);
    
    // Test 2: TOP_A, size=5, offset=2 (third element in chunk)
    int *input_array2 = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        input_array2[i] = data->a.stack[i];
    }
    
    t_chunk chunk2 = {TOP_A, 5};
    int result2 = chunk_value(data, &chunk2, 2);
    
    tests[1] = create_chunk_value_test(2, "TOP_A_middle", input_array2, size, result2, "TOP_A", 5, 2);
    
    // Test 3: BOTTOM_B, size=4, offset=0 (first element in chunk)
    int *input_array3 = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        input_array3[i] = data->b.stack[i];
    }
    
    t_chunk chunk3 = {BOTTOM_B, 4};
    int result3 = chunk_value(data, &chunk3, 0);
    
    tests[2] = create_chunk_value_test(3, "BOTTOM_B_basic", input_array3, size, result3, "BOTTOM_B", 4, 0);
    
    // Test 4: BOTTOM_B, size=4, offset=1 (second element in chunk)
    int *input_array4 = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        input_array4[i] = data->b.stack[i];
    }
    
    t_chunk chunk4 = {BOTTOM_B, 4};
    int result4 = chunk_value(data, &chunk4, 1);
    
    tests[3] = create_chunk_value_test(4, "BOTTOM_B_second", input_array4, size, result4, "BOTTOM_B", 4, 1);
    
    // Test 5: TOP_B, size=3, offset=2 (last element in chunk)
    int *input_array5 = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        input_array5[i] = data->b.stack[i];
    }
    
    t_chunk chunk5 = {TOP_B, 3};
    int result5 = chunk_value(data, &chunk5, 2);
    
    tests[4] = create_chunk_value_test(5, "TOP_B_last", input_array5, size, result5, "TOP_B", 3, 2);
    
    // Save results to JSON file
    save_chunk_value_tests_to_json(tests, 5, "chunk_value.json");
    
    // Cleanup
    for (int i = 0; i < 5; i++) {
        if (tests[i]) {
            free_chunk_value_test(tests[i]);
        }
    }
    cleanup_test_data(data);

    return 0;
}


