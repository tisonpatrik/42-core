#include "../../../libs/push_swap/src/models.h"
#include "../../../include/chunk_utils_task.h"
#include "../../../include/chunk_utils_common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Forward declaration of the function to test
t_stack	*loc_to_stack(t_ps *data, t_loc loc);

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

// Main function to run loc_to_stack tests - UNIFIED APPROACH!
int run_loc_to_stack_tests(int size) {
	t_ps *data = create_test_data(size, size);
	if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
	
	// Create test data structure
    t_loc_to_stack_test test_data;
    
    // Test 1: TOP_A
    test_data.top_a_result = test_loc_to_stack_top_a(data);
    
    // Test 2: BOTTOM_A
    test_data.bottom_a_result = test_loc_to_stack_bottom_a(data);
    
    // Test 3: TOP_B
    test_data.top_b_result = test_loc_to_stack_top_b(data);
    
    // Test 4: BOTTOM_B
    test_data.bottom_b_result = test_loc_to_stack_bottom_b(data);
    
    // Copy stack data for JSON export
    test_data.stack_a_data = malloc(size * sizeof(int));
    test_data.stack_a_size = size;
    test_data.stack_b_data = malloc(size * sizeof(int));
    test_data.stack_b_size = size;
    
    if (test_data.stack_a_data && test_data.stack_b_data) {
        // Copy stack A data
        for (int i = 0; i < size; i++) {
            test_data.stack_a_data[i] = data->a.stack[i];
        }
        
        // Copy stack B data
        for (int i = 0; i < size; i++) {
            test_data.stack_b_data[i] = data->b.stack[i];
        }
        
        // Save results using specific function - UNIFIED WITH OTHER TESTS!
        save_loc_to_stack_results(data, &test_data);
        
        // Cleanup test data
        free(test_data.stack_a_data);
        free(test_data.stack_b_data);
    }

    // Cleanup
    cleanup_test_data(data);

    return 0;
}

// Business logic function to save loc_to_stack test results
void save_loc_to_stack_results(t_ps *data __attribute__((unused)), t_loc_to_stack_test *test_data) {
    if (!test_data) return;
    
    // Create test batch
    t_test_batch *batch = create_test_batch("loc_to_stack", 4);
    if (!batch) return;
    
    // Create test cases using the clean utility functions
    t_test_case test1 = {0};
    test1.id = 1;
    test1.name = "TOP_A";
    test1.input_array = test_data->stack_a_data;
    test1.array_size = test_data->stack_a_size;
    test1.result = test_data->top_a_result;
    test1.param1_name = "stack_loc";
    test1.param1_value = "TOP_A";
    
    t_test_case test2 = {0};
    test2.id = 2;
    test2.name = "BOTTOM_A";
    test2.input_array = test_data->stack_a_data;
    test2.array_size = test_data->stack_a_size;
    test2.result = test_data->bottom_a_result;
    test2.param1_name = "stack_loc";
    test2.param1_value = "BOTTOM_A";
    
    t_test_case test3 = {0};
    test3.id = 3;
    test3.name = "TOP_B";
    test3.input_array = test_data->stack_b_data;
    test3.array_size = test_data->stack_b_size;
    test3.result = test_data->top_b_result;
    test3.param1_name = "stack_loc";
    test3.param1_value = "TOP_B";
    
    t_test_case test4 = {0};
    test4.id = 4;
    test4.name = "BOTTOM_B";
    test4.input_array = test_data->stack_b_data;
    test4.array_size = test_data->stack_b_size;
    test4.result = test_data->bottom_b_result;
    test4.param1_name = "stack_loc";
    test4.param1_value = "BOTTOM_B";
    
    // Add tests to batch
    add_test_to_batch(batch, 0, &test1);
    add_test_to_batch(batch, 1, &test2);
    add_test_to_batch(batch, 2, &test3);
    add_test_to_batch(batch, 3, &test4);
    
    // Save to file using the clean utility function
    save_test_batch_to_json(batch, "loc_to_stack.json");
    
    // Cleanup
    free_test_batch(batch);
}
