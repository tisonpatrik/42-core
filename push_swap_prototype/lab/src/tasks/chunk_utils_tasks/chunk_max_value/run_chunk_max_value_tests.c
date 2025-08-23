#include "../../../../include/chunk_max_value_test.h"
#include "../../../../include/stack_utils.h"
#include "../../../../include/json_utils.h"
#include "../../../../libs/push_swap/src/chunk_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants to replace magic numbers
#define TEST_COUNT 4
#define TOP_A_CHUNK_SIZE 5
#define BOTTOM_A_CHUNK_SIZE 4
#define TOP_B_CHUNK_SIZE 3
#define BOTTOM_B_CHUNK_SIZE 4

// Functions are implemented in libs/push_swap/src/chunk_utils.c

// Test functions to return results instead of printing
int test_chunk_max_value_top_a(t_ps *data) {
    t_chunk chunk = {TOP_A, TOP_A_CHUNK_SIZE};
    return chunk_max_value(data, &chunk);
}

int test_chunk_max_value_bottom_a(t_ps *data) {
    t_chunk chunk = {BOTTOM_A, BOTTOM_A_CHUNK_SIZE};
    return chunk_max_value(data, &chunk);
}

int test_chunk_max_value_top_b(t_ps *data) {
    t_chunk chunk = {TOP_B, TOP_B_CHUNK_SIZE};
    return chunk_max_value(data, &chunk);
}

int test_chunk_max_value_bottom_b(t_ps *data) {
    t_chunk chunk = {BOTTOM_B, BOTTOM_B_CHUNK_SIZE};
    return chunk_max_value(data, &chunk);
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
static int create_all_test_cases(t_ps *data, t_chunk_max_value_test **tests, 
                                int *chunk_data, int size) {
    // Test 1: Top A chunk max value
    int max_value_a = test_chunk_max_value_top_a(data);
    tests[0] = create_chunk_max_value_test(1, "TOP_A", chunk_data, size, max_value_a, "TOP_A", TOP_A_CHUNK_SIZE);
    
    // Test 2: Bottom A chunk max value
    int max_value_b = test_chunk_max_value_bottom_a(data);
    tests[1] = create_chunk_max_value_test(2, "BOTTOM_A", chunk_data, size, max_value_b, "BOTTOM_A", BOTTOM_A_CHUNK_SIZE);
    
    // Test 3: Top B chunk max value
    int top_b_max = test_chunk_max_value_top_b(data);
    tests[2] = create_chunk_max_value_test(3, "TOP_B", chunk_data, size, top_b_max, "TOP_B", TOP_B_CHUNK_SIZE);
    
    // Test 4: Bottom B chunk max value
    int bottom_b_max = test_chunk_max_value_bottom_b(data);
    tests[3] = create_chunk_max_value_test(4, "BOTTOM_B", chunk_data, size, bottom_b_max, "BOTTOM_B", BOTTOM_B_CHUNK_SIZE);
    
    // Check if all tests were created successfully
    for (int i = 0; i < TEST_COUNT; i++) {
        if (!tests[i]) return 0; // Failed to create a test
    }
    return 1; // All tests created successfully
}

// Helper function to cleanup test resources
static void cleanup_test_resources(t_chunk_max_value_test **tests) {
    for (int i = 0; i < TEST_COUNT; i++) {
        if (tests[i]) {
            free_chunk_max_value_test(tests[i]);
        }
    }
}

// Main function to run chunk_max_value tests
int run_chunk_max_value_tests(int size) {
    t_ps *data = create_test_data(size, size);
    if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
    
    // Create array of test cases
    t_chunk_max_value_test *tests[TEST_COUNT] = {NULL};
    
    // Copy chunk data for JSON export
    int *chunk_data = copy_stack_data(data->a.stack, size);
    if (!chunk_data) {
        printf("Failed to allocate chunk data\n");
        cleanup_test_data(data);
        return 1;
    }
    
    // Create all test cases
    if (!create_all_test_cases(data, tests, chunk_data, size)) {
        printf("Failed to create test cases\n");
        free(chunk_data);
        cleanup_test_resources(tests);
        cleanup_test_data(data);
        return 1;
    }
    
    // Save results to JSON file
    save_tests_to_json_generic("chunk_max_value.json", "chunk_max_value", (void**)tests, TEST_COUNT, add_chunk_max_value_test_data);
    
    // Cleanup
    free(chunk_data);
    cleanup_test_resources(tests);
    cleanup_test_data(data);

    return 0;
}
