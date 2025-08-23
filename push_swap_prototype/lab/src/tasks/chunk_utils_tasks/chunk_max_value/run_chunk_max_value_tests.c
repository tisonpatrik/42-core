#include "../../../../include/testing/chunk_max_value_test.h"
#include "../../../../include/utils/stack_utils.h"
#include "../../../../include/utils/json_utils.h"
#include "../../../../include/testing/chunk_utils_tests.h"
#include "../../../../include/testing/test_utils.h"
#include "../../../../libs/push_swap/src/chunk_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions are implemented in libs/push_swap/src/chunk_utils.c

// Test functions to return results instead of printing
int test_chunk_max_value_top_a(t_ps *data, const t_test_config *config) {
    t_chunk chunk = {TOP_A, config->chunk_sizes.top_a_size};
    return chunk_max_value(data, &chunk);
}

int test_chunk_max_value_bottom_a(t_ps *data, const t_test_config *config) {
    t_chunk chunk = {BOTTOM_A, config->chunk_sizes.bottom_a_size};
    return chunk_max_value(data, &chunk);
}

int test_chunk_max_value_top_b(t_ps *data, const t_test_config *config) {
    t_chunk chunk = {TOP_B, config->chunk_sizes.top_b_size};
    return chunk_max_value(data, &chunk);
}

int test_chunk_max_value_bottom_b(t_ps *data, const t_test_config *config) {
    t_chunk chunk = {BOTTOM_B, config->chunk_sizes.bottom_b_size};
    return chunk_max_value(data, &chunk);
}

// Helper function to create all test cases
static int create_all_test_cases(t_ps *data, t_chunk_max_value_test **tests, 
                                int *chunk_data, int size, const t_test_config *config) {
    // Test 1: Top A chunk max value
    int max_value_a = test_chunk_max_value_top_a(data, config);
    tests[0] = create_chunk_max_value_test(1, "TOP_A", chunk_data, size, max_value_a, "TOP_A", config->chunk_sizes.top_a_size);
    
    // Test 2: Bottom A chunk max value
    int max_value_b = test_chunk_max_value_bottom_a(data, config);
    tests[1] = create_chunk_max_value_test(2, "BOTTOM_A", chunk_data, size, max_value_b, "BOTTOM_A", config->chunk_sizes.bottom_a_size);
    
    // Test 3: Top B chunk max value
    int top_b_max = test_chunk_max_value_top_b(data, config);
    tests[2] = create_chunk_max_value_test(3, "TOP_B", chunk_data, size, top_b_max, "TOP_B", config->chunk_sizes.top_b_size);
    
    // Test 4: Bottom B chunk max value
    int bottom_b_max = test_chunk_max_value_bottom_b(data, config);
    tests[3] = create_chunk_max_value_test(4, "BOTTOM_B", chunk_data, size, bottom_b_max, "BOTTOM_B", config->chunk_sizes.bottom_b_size);
    
    // Check if all tests were created successfully
    for (int i = 0; i < config->test_counts.chunk_max_value_count; i++) {
        if (!tests[i]) return 0; // Failed to create a test
    }
    return 1; // All tests created successfully
}

// Main function to run chunk_max_value tests
int run_chunk_max_value_tests(int size) {
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
    t_chunk_max_value_test *tests[4] = {NULL}; // Fixed size for now
    
    // Copy chunk data for JSON export
    int *chunk_data = copy_stack_data(data->a.stack, size);
    if (!chunk_data) {
        printf("Failed to allocate chunk data\n");
        cleanup_test_data(data);
        free_test_config(config);
        return 1;
    }
    
    // Create all test cases
    if (!create_all_test_cases(data, tests, chunk_data, size, config)) {
        printf("Failed to create test cases\n");
        free(chunk_data);
        cleanup_test_data(data);
        free_test_config(config);
        return 1;
    }
    
    // Save results to JSON file
    save_tests_to_json_generic("chunk_max_value.json", "chunk_max_value", (void**)tests, config->test_counts.chunk_max_value_count, add_chunk_max_value_test_data);
    
    // Cleanup
    free(chunk_data);
    for (int i = 0; i < config->test_counts.chunk_max_value_count; i++) {
        if (tests[i]) {
            free_chunk_max_value_test(tests[i]);
        }
    }
    cleanup_test_data(data);
    free_test_config(config);

    return 0;
}
