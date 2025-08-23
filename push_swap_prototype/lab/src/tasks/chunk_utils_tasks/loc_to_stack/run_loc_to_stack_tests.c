#include "../../../../include/loc_to_stack_test.h"
#include "../../../../include/stack_utils.h"
#include "../../../../libs/push_swap/src/chunk_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Constants to replace magic numbers
#define TEST_COUNT 4

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

// Helper function to copy stack data
static int* copy_stack_data(const int *source, int size) {
    int *copy = malloc(size * sizeof(int));
    if (!copy) return NULL;
    
    for (int i = 0; i < size; i++) {
        copy[i] = source[i];
    }
    return copy;
}

// Helper function to create all test cases
static int create_all_test_cases(t_ps *data, t_loc_to_stack_test **tests, 
                                int *stack_a_data, int *stack_b_data, int size) {
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
    for (int i = 0; i < TEST_COUNT; i++) {
        if (!tests[i]) return 0; // Failed to create a test
    }
    return 1; // All tests created successfully
}

// Helper function to cleanup test resources
static void cleanup_test_resources(t_loc_to_stack_test **tests) {
    for (int i = 0; i < TEST_COUNT; i++) {
        if (tests[i]) {
            free_loc_to_stack_test(tests[i]);
        }
    }
}

// Main function to run loc_to_stack tests
int run_loc_to_stack_tests(int size) {
    t_ps *data = create_test_data(size, size);
    if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
    
    // Create array of test cases
    t_loc_to_stack_test *tests[TEST_COUNT] = {NULL};
    
    // Copy stack data for JSON export
    int *stack_a_data = copy_stack_data(data->a.stack, size);
    int *stack_b_data = copy_stack_data(data->b.stack, size);
    if (!stack_a_data || !stack_b_data) {
        printf("Failed to allocate stack data\n");
        if (stack_a_data) free(stack_a_data);
        if (stack_b_data) free(stack_b_data);
        cleanup_test_data(data);
        return 1;
    }
    
    // Create all test cases
    if (!create_all_test_cases(data, tests, stack_a_data, stack_b_data, size)) {
        printf("Failed to create test cases\n");
        free(stack_a_data);
        free(stack_b_data);
        cleanup_test_resources(tests);
        cleanup_test_data(data);
        return 1;
    }
    
    // Save results to JSON file
    save_loc_to_stack_tests_to_json(tests, TEST_COUNT, "loc_to_stack.json");
    
    // Cleanup
    free(stack_a_data);
    free(stack_b_data);
    cleanup_test_resources(tests);
    cleanup_test_data(data);

    return 0;
}
