#include "../../../../include/testing/loc_to_stack_test.h"
#include "../../../../include/utils/stack_utils.h"
#include "../../../../include/utils/json_utils.h"
#include "../../../../libs/push_swap/src/chunk_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Simple test: Arrange, Act, Assert, Output to JSON
int run_loc_to_stack_tests(int size) {
    // ARRANGE: Create test data
    t_ps *data = create_test_data(size, size);
    if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
    
    // Create test cases array
    t_loc_to_stack_test *tests[4] = {NULL};
    
    // ACT & ASSERT: Run tests and capture results
    // Test 1: TOP_A
    t_stack *result1 = loc_to_stack(data, TOP_A);
    tests[0] = create_loc_to_stack_test(1, "TOP_A", data->a.stack, size, 
                                       result1->stack[result1->top], "TOP_A");
    
    // Test 2: BOTTOM_A
    t_stack *result2 = loc_to_stack(data, BOTTOM_A);
    tests[1] = create_loc_to_stack_test(2, "BOTTOM_A", data->a.stack, size, 
                                       result2->stack[result2->bottom], "BOTTOM_A");
    
    // Test 3: TOP_B
    t_stack *result3 = loc_to_stack(data, TOP_B);
    tests[2] = create_loc_to_stack_test(3, "TOP_B", data->b.stack, size, 
                                       result3->stack[result3->top], "TOP_B");
    
    // Test 4: BOTTOM_B
    t_stack *result4 = loc_to_stack(data, BOTTOM_B);
    tests[3] = create_loc_to_stack_test(4, "BOTTOM_B", data->b.stack, size, 
                                       result4->stack[result4->bottom], "BOTTOM_B");
    
    // OUTPUT: Save to JSON
    save_tests_to_json_generic("loc_to_stack.json", "loc_to_stack", (void**)tests, 4, add_loc_to_stack_test_data);
    
    // Cleanup
    for (int i = 0; i < 4; i++) {
        if (tests[i]) free_loc_to_stack_test(tests[i]);
    }
    cleanup_test_data(data);
    
    return 0;
}
