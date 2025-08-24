#include "../../../../include/chunk_split_test.h"
#include "../../../../include/utils/stack_utils.h"
#include "../../../../include/utils/json_utils.h"
#include "../../../../libs/push_swap/src/models.h"
#include <stdio.h>
#include <stdlib.h>


// Simple test: Arrange, Act, Assert, Output to JSON
int run_chunk_split_tests(int size) {
    // ARRANGE: Create test data
    t_ps *data = create_test_data(size, size);
    if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
    
    // Create test cases array
    t_chunk_split_test *tests[4] = {NULL};
    
    // ACT & ASSERT: Run tests and capture results
    // Test 1: TOP_A chunk split with size 15
    int min_size1, mid_size1, max_size1;
    
    tests[0] = create_chunk_split_test(1, "TOP_A_split", data->a.stack, size, 
                                       15, "TOP_A", 
                                       min_size1, mid_size1, max_size1,
                                       "BOTTOM_B", "TOP_B", "BOTTOM_A");
    
    // Test 2: BOTTOM_A chunk split with size 12
    int min_size2, mid_size2, max_size2;
    
    tests[1] = create_chunk_split_test(2, "BOTTOM_A_split", data->a.stack, size, 
                                       12, "BOTTOM_A", 
                                       min_size2, mid_size2, max_size2,
                                       "BOTTOM_B", "TOP_B", "TOP_A");
    
    // Test 3: TOP_B chunk split with size 10
    int min_size3, mid_size3, max_size3;
    
    tests[2] = create_chunk_split_test(3, "TOP_B_split", data->b.stack, size, 
                                       10, "TOP_B", 
                                       min_size3, mid_size3, max_size3,
                                       "BOTTOM_B", "BOTTOM_A", "TOP_A");
    
    // Test 4: BOTTOM_B chunk split with size 8
    int min_size4, mid_size4, max_size4;
    
    tests[3] = create_chunk_split_test(4, "BOTTOM_B_split", data->b.stack, size, 
                                       8, "BOTTOM_B", 
                                       min_size4, mid_size4, max_size4,
                                       "TOP_B", "BOTTOM_A", "TOP_A");
    
    // OUTPUT: Save to JSON
    save_tests_to_json_generic("chunk_split.json", "chunk_split", (void**)tests, 4, add_chunk_split_test_data);
    
    // Cleanup
    for (int i = 0; i < 4; i++) {
        if (tests[i]) free_chunk_split_test(tests[i]);
    }
    cleanup_test_data(data);
    
    return 0;
}
