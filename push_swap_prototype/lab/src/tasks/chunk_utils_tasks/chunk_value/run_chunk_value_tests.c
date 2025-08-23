#include "../../../../include/testing/chunk_value_test.h"
#include "../../../../include/utils/stack_utils.h"
#include "../../../../include/utils/json_utils.h"
#include "../../../../libs/push_swap/src/chunk_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Simple test: Arrange, Act, Assert, Output to JSON
int run_chunk_value_tests(int size) {
    // ARRANGE: Create test data
    t_ps *data = create_test_data(size, size);
    if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
    
    // Create test cases array
    t_chunk_value_test *tests[5] = {NULL};
    
    // ACT & ASSERT: Run tests and capture results
    // Test 1: TOP_A, size=5, offset=0 (first element in chunk)
    t_chunk chunk1 = {TOP_A, 5};
    int result1 = chunk_value(data, &chunk1, 0);
    tests[0] = create_chunk_value_test(1, "TOP_A_basic", data->a.stack, size, result1, "TOP_A", 5, 0);
    
    // Test 2: TOP_A, size=5, offset=2 (third element in chunk)
    int result2 = chunk_value(data, &chunk1, 2);
    tests[1] = create_chunk_value_test(2, "TOP_A_middle", data->a.stack, size, result2, "TOP_A", 5, 2);
    
    // Test 3: BOTTOM_B, size=4, offset=0 (first element in chunk)
    t_chunk chunk2 = {BOTTOM_B, 4};
    int result3 = chunk_value(data, &chunk2, 0);
    tests[2] = create_chunk_value_test(3, "BOTTOM_B_basic", data->b.stack, size, result3, "BOTTOM_B", 4, 0);
    
    // Test 4: BOTTOM_B, size=4, offset=1 (second element in chunk)
    int result4 = chunk_value(data, &chunk2, 1);
    tests[3] = create_chunk_value_test(4, "BOTTOM_B_second", data->b.stack, size, result4, "BOTTOM_B", 4, 1);
    
    // Test 5: TOP_B, size=3, offset=2 (last element in chunk)
    t_chunk chunk3 = {TOP_B, 3};
    int result5 = chunk_value(data, &chunk3, 2);
    tests[4] = create_chunk_value_test(5, "TOP_B_last", data->b.stack, size, result5, "TOP_B", 3, 2);
    
    // OUTPUT: Save to JSON
    save_tests_to_json_generic("chunk_value.json", "chunk_value", (void**)tests, 5, add_chunk_value_test_data);
    
    // Cleanup
    for (int i = 0; i < 5; i++) {
        if (tests[i]) free_chunk_value_test(tests[i]);
    }
    cleanup_test_data(data);
    
    return 0;
}


