#include "../../../include/chunk_utils_task.h"
#include "../../../include/json_utils.h"
#include "../../../include/stack_utils.h"
#include "../../../include/test_utils.h"
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
	
	// Create test batch with 4 test cases
    t_test_batch *batch = create_test_batch("loc_to_stack", 4);
    if (!batch) {
        printf("Failed to create test batch\n");
        cleanup_test_data(data);
        return 1;
    }
    
    // Copy stack data for JSON export
    int *stack_a_data = malloc(size * sizeof(int));
    int *stack_b_data = malloc(size * sizeof(int));
    if (!stack_a_data || !stack_b_data) {
        printf("Failed to allocate stack data\n");
        if (stack_a_data) free(stack_a_data);
        if (stack_b_data) free(stack_b_data);
        free_test_batch(batch);
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
    t_test_case *test1 = create_test_case(1, "TOP_A", stack_a_data, size, top_a_result);
    set_test_param1(test1, "stack_loc", "TOP_A");
    add_test_to_batch(batch, 0, test1);
    
    // Test 2: BOTTOM_A
    int bottom_a_result = test_loc_to_stack_bottom_a(data);
    t_test_case *test2 = create_test_case(2, "BOTTOM_A", stack_a_data, size, bottom_a_result);
    set_test_param1(test2, "stack_loc", "BOTTOM_A");
    add_test_to_batch(batch, 1, test2);
    
    // Test 3: TOP_B
    int top_b_result = test_loc_to_stack_top_b(data);
    t_test_case *test3 = create_test_case(3, "TOP_B", stack_b_data, size, top_b_result);
    set_test_param1(test3, "stack_loc", "TOP_B");
    add_test_to_batch(batch, 2, test3);
    
    // Test 4: BOTTOM_B
    int bottom_b_result = test_loc_to_stack_bottom_b(data);
    t_test_case *test4 = create_test_case(4, "BOTTOM_B", stack_b_data, size, bottom_b_result);
    set_test_param1(test4, "stack_loc", "BOTTOM_B");
    add_test_to_batch(batch, 3, test4);
    
    // Save results to JSON file
    save_test_batch_to_json(batch, "loc_to_stack.json");
    
    // Cleanup
    free(stack_a_data);
    free(stack_b_data);
    free_test_batch(batch);
    cleanup_test_data(data);

    return 0;
}

// Function removed - now using generic t_test_batch approach directly
