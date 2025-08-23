#include "../../../libs/push_swap/src/models.h"
#include "../../../include/chunk_utils_task.h"
#include "../../../include/chunk_utils_common.h"
#include <stdbool.h>
#include <stdio.h>

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
