#include "../../../../include/testing/chunk_max_value_test.h"
#include "../../../../include/utils/stack_utils.h"
#include "../../../../include/utils/json_utils.h"
#include "../../../../libs/push_swap/src/chunk_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Simple test: Arrange, Act, Assert, Output to JSON
int run_chunk_max_value_tests(int size) {
    // ARRANGE: Create test data
    t_ps *data = create_test_data(size, size);
    if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
    
    // Create test cases array
    t_chunk_max_value_test *tests[4] = {NULL};
    
    // ACT & ASSERT: Run tests and capture results
    // Test 1: TOP_A chunk max value
    t_chunk chunk1 = {TOP_A, 5};
    int max_value_a = chunk_max_value(data, &chunk1);
    tests[0] = create_chunk_max_value_test(1, "TOP_A", data->a.stack, size, max_value_a, "TOP_A", 5);
    
    // Test 2: BOTTOM_A chunk max value
    t_chunk chunk2 = {BOTTOM_A, 4};
    int max_value_b = chunk_max_value(data, &chunk2);
    tests[1] = create_chunk_max_value_test(2, "BOTTOM_A", data->a.stack, size, max_value_b, "BOTTOM_A", 4);
    
    // Test 3: TOP_B chunk max value - FIXED: Use stack B data
    t_chunk chunk3 = {TOP_B, 3};
    int top_b_max = chunk_max_value(data, &chunk3);
    tests[2] = create_chunk_max_value_test(3, "TOP_B", data->b.stack, size, top_b_max, "TOP_B", 3);
    
    // Test 4: BOTTOM_B chunk max value - FIXED: Use stack B data
    t_chunk chunk4 = {BOTTOM_B, 4};
    int bottom_b_max = chunk_max_value(data, &chunk4);
    tests[3] = create_chunk_max_value_test(4, "BOTTOM_B", data->b.stack, size, bottom_b_max, "BOTTOM_B", 4);
    
    // OUTPUT: Save to JSON
    save_tests_to_json_generic("chunk_max_value.json", "chunk_max_value", (void**)tests, 4, add_chunk_max_value_test_data);
    
    // Cleanup
    for (int i = 0; i < 4; i++) {
        if (tests[i]) free_chunk_max_value_test(tests[i]);
    }
    cleanup_test_data(data);
    
    return 0;
}
