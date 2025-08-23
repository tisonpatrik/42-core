#include "../../../include/chunk_utils_task.h"
#include "../../../include/specific_test_utils.h"
#include "../../../include/specific_json_utils.h"
#include "../../../include/stack_utils.h"
#include "../../../libs/push_swap/src/chunk_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Function is implemented in libs/push_swap/src/chunk_utils.c

// Clean test functions - ONLY test logic, no test case creation
int test_loc_to_stack_top_a(t_ps *data) {
    t_stack *result = loc_to_stack(data, TOP_A);
    return result->stack[result->top];
}

int test_loc_to_stack_bottom_a(t_ps *data) {
    t_stack *result = loc_to_stack(data, BOTTOM_A);
    return result->stack[result->bottom];
}

int test_loc_to_stack_top_b(t_ps *data) {
    t_stack *result = loc_to_stack(data, TOP_B);
    return result->stack[result->top];
}

int test_loc_to_stack_bottom_b(t_ps *data) {
    t_stack *result = loc_to_stack(data, BOTTOM_B);
    return result->stack[result->bottom];
}

// Main function to run loc_to_stack tests
int run_loc_to_stack_tests(int size) {
	t_ps *data = create_test_data(size, size);
	if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
	
	// Create array of 4 test cases
    t_loc_to_stack_test *tests[4] = {NULL};
    
    // Copy stack data for JSON export
    int *stack_a_data = malloc(size * sizeof(int));
    int *stack_b_data = malloc(size * sizeof(int));
    if (!stack_a_data || !stack_b_data) {
        printf("Failed to allocate stack data\n");
        if (stack_a_data) free(stack_a_data);
        if (stack_b_data) free(stack_b_data);
        cleanup_test_data(data);
        return 1;
    }
    
    // Copy stack A data
    for (int i = 0; i < size; i++) {
        stack_a_data[i] = data->a.stack[i];
    }
    
    // Copy stack B data
    for (int i = 0; i < size; i++) {
        stack_b_data[i] = data->b.stack[i];
    }
    
    // Test 1: TOP_A
    int top_a_result = test_loc_to_stack_top_a(data);
    tests[0] = create_loc_to_stack_test(1, "TOP_A", stack_a_data, size, top_a_result, "TOP_A");
    
    // Test 2: BOTTOM_A
    int bottom_a_result = test_loc_to_stack_bottom_a(data);
    tests[1] = create_loc_to_stack_test(2, "BOTTOM_A", stack_a_data, size, bottom_a_result, "BOTTOM_A");
    
    // Test 3: TOP_B
    int top_b_result = test_loc_to_stack_top_b(data);
    tests[2] = create_loc_to_stack_test(3, "TOP_B", stack_b_data, size, top_b_result, "TOP_B");
    
    // Test 4: BOTTOM_B
    int bottom_b_result = test_loc_to_stack_bottom_b(data);
    tests[3] = create_loc_to_stack_test(4, "BOTTOM_B", stack_b_data, size, bottom_b_result, "BOTTOM_B");
    
    // Save results to JSON file
    save_loc_to_stack_tests_to_json(tests, 4, "loc_to_stack.json");
    
    // Cleanup
    free(stack_a_data);
    free(stack_b_data);
    for (int i = 0; i < 4; i++) {
        if (tests[i]) {
            free_loc_to_stack_test(tests[i]);
        }
    }
    cleanup_test_data(data);

    return 0;
}
