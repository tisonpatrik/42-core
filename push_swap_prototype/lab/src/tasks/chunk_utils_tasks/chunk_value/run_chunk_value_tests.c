#include "../../../../include/testing/chunk_value_test.h"
#include "../../../../include/utils/stack_utils.h"
#include "../../../../include/utils/json_utils.h"
#include "../../../../include/testing/chunk_utils_tests.h"
#include "../../../../include/testing/test_config.h"
#include "../../../../include/testing/test_utils.h"
#include "../../../../libs/push_swap/src/chunk_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Functions are implemented in libs/push_swap/src/chunk_utils.c

// Test functions to return results instead of printing
int test_chunk_value_top_a_basic(t_ps *data, const t_test_config *config) {
    t_chunk chunk = {TOP_A, config->chunk_sizes.top_a_size};
    return chunk_value(data, &chunk, 0); // First element
}

int test_chunk_value_top_a_middle(t_ps *data, const t_test_config *config) {
    t_chunk chunk = {TOP_A, config->chunk_sizes.top_a_size};
    return chunk_value(data, &chunk, 2); // Third element
}

int test_chunk_value_bottom_b_basic(t_ps *data, const t_test_config *config) {
    t_chunk chunk = {BOTTOM_B, config->chunk_sizes.bottom_b_size};
    return chunk_value(data, &chunk, 0); // Bottom element
}

int test_chunk_value_bottom_b_second(t_ps *data, const t_test_config *config) {
    t_chunk chunk = {BOTTOM_B, config->chunk_sizes.bottom_b_size};
    return chunk_value(data, &chunk, 1); // Second from bottom
}

int test_chunk_value_top_b_last(t_ps *data, const t_test_config *config) {
    t_chunk chunk = {TOP_B, config->chunk_sizes.top_b_size};
    return chunk_value(data, &chunk, 2); // Last element in chunk
}

// Helper function to create a single test case
static t_chunk_value_test* create_single_test_case(int test_id, const char *test_name, 
                                                  t_ps *data, t_loc loc, int chunk_size, 
                                                  int offset, const char *stack_name) {
    int *input_array = copy_stack_data(
        (loc == TOP_A || loc == BOTTOM_A) ? data->a.stack : data->b.stack, 
        data->a.size
    );
    if (!input_array) return NULL;
    
    t_chunk chunk = {loc, chunk_size};
    int result = chunk_value(data, &chunk, offset);
    
    return create_chunk_value_test(test_id, test_name, input_array, data->a.size, 
                                  result, stack_name, chunk_size, offset);
}

// Helper function to run all test cases
static int run_all_test_cases(t_ps *data, t_chunk_value_test **tests, const t_test_config *config) {
    // Test 1: TOP_A, size=5, offset=0 (first element in chunk)
    tests[0] = create_single_test_case(1, "TOP_A_basic", data, TOP_A, config->chunk_sizes.top_a_size, 0, "TOP_A");
    
    // Test 2: TOP_A, size=5, offset=2 (third element in chunk)
    tests[1] = create_single_test_case(2, "TOP_A_middle", data, TOP_A, config->chunk_sizes.top_a_size, 2, "TOP_A");
    
    // Test 3: BOTTOM_B, size=4, offset=0 (first element in chunk)
    tests[2] = create_single_test_case(3, "BOTTOM_B_basic", data, BOTTOM_B, config->chunk_sizes.bottom_b_size, 0, "BOTTOM_B");
    
    // Test 4: BOTTOM_B, size=4, offset=1 (second element in chunk)
    tests[3] = create_single_test_case(4, "BOTTOM_B_second", data, BOTTOM_B, config->chunk_sizes.bottom_b_size, 1, "BOTTOM_B");
    
    // Test 5: TOP_B, size=3, offset=2 (last element in chunk)
    tests[4] = create_single_test_case(5, "TOP_B_last", data, TOP_B, config->chunk_sizes.top_b_size, 2, "TOP_B");
    
    // Check if all tests were created successfully
    for (int i = 0; i < config->test_counts.chunk_value_count; i++) {
        if (!tests[i]) return 0; // Failed to create a test
    }
    return 1; // All tests created successfully
}

// Main function to run chunk_value tests
int run_chunk_value_tests(int size) {
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
    t_chunk_value_test *tests[5] = {NULL}; // Fixed size for now
    
    // Run all test cases
    if (!run_all_test_cases(data, tests, config)) {
        printf("Failed to create test cases\n");
        cleanup_test_data(data);
        free_test_config(config);
        return 1;
    }
    
    // Save results to JSON file
    save_tests_to_json_generic("chunk_value.json", "chunk_value", (void**)tests, config->test_counts.chunk_value_count, add_chunk_value_test_data);
    
    // Cleanup
    for (int i = 0; i < config->test_counts.chunk_value_count; i++) {
        if (tests[i]) {
            free_chunk_value_test(tests[i]);
        }
    }
    cleanup_test_data(data);
    free_test_config(config);

    return 0;
}


