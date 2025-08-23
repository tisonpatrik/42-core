#include "../../../../include/testing/loc_to_stack_test.h"
#include "../../../../include/utils/stack_utils.h"
#include "../../../../include/utils/json_utils.h"
#include "../../../../include/testing/chunk_utils_tests.h"
#include "../../../../include/testing/test_config.h"
#include "../../../../include/testing/test_utils.h"
#include "../../../../libs/push_swap/src/chunk_utils.h"
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

// Helper function to create all test cases
static int create_all_test_cases(t_ps *data, t_loc_to_stack_test **tests, 
                                int *stack_a_data, int *stack_b_data, int size, const t_test_config *config) {
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
    
    // Check if all tests were created successfully
    for (int i = 0; i < config->test_counts.loc_to_stack_count; i++) {
        if (!tests[i]) return 0; // Failed to create a test
    }
    return 1; // All tests created successfully
}

// Main function to run loc_to_stack tests
int run_loc_to_stack_tests(int size) {
    // Get default configuration
    t_test_config *config = get_default_test_config();
    if (!config) {
        printf("Failed to create test configuration\n");
        return 1;
    }
    
    t_ps *data = create_test_data(size, size);
    if (!data) {
        printf("Failed to create test data\n");
        free_test_config(config);
        return 1;
    }
    
    // Create array of test cases
    t_loc_to_stack_test *tests[4] = {NULL}; // Fixed size for now
    
    // Copy stack data for JSON export
    int *stack_a_data = copy_stack_data(data->a.stack, size);
    int *stack_b_data = copy_stack_data(data->b.stack, size);
    if (!stack_a_data || !stack_b_data) {
        printf("Failed to allocate stack data\n");
        if (stack_a_data) free(stack_a_data);
        if (stack_b_data) free(stack_b_data);
        cleanup_test_data(data);
        free_test_config(config);
        return 1;
    }
    
    // Create all test cases
    if (!create_all_test_cases(data, tests, stack_a_data, stack_b_data, size, config)) {
        printf("Failed to create test cases\n");
        free(stack_a_data);
        free(stack_b_data);
        cleanup_test_data(data);
        free_test_config(config);
        return 1;
    }
    
    // Save results to JSON file
    save_tests_to_json_generic("loc_to_stack.json", "loc_to_stack", (void**)tests, config->test_counts.loc_to_stack_count, add_loc_to_stack_test_data);
    
    // Cleanup
    free(stack_a_data);
    free(stack_b_data);
    for (int i = 0; i < config->test_counts.loc_to_stack_count; i++) {
        if (tests[i]) {
            free_loc_to_stack_test(tests[i]);
        }
    }
    cleanup_test_data(data);
    free_test_config(config);

    return 0;
}
