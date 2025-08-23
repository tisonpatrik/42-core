#include "../../../libs/push_swap/src/models.h"
#include "../../../include/chunk_utils_task.h"
#include "../../../include/chunk_utils_common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Forward declaration of the function to test
t_stack	*loc_to_stack(t_ps *data, t_loc loc);

// Test functions to return results instead of printing
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
	
	// Initialize test data structure
    t_loc_to_stack_test test_data = {0};
    
    // Test 1: TOP_A
    test_data.test1_top_a.input_array = malloc(size * sizeof(int));
    test_data.test1_top_a.array_size = size;
    test_data.test1_top_a.stack_loc = TOP_A;
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test1_top_a.input_array[i] = data->a.stack[i];
    }
    
    // Run test
    t_stack *result1 = loc_to_stack(data, TOP_A);
    test_data.test1_top_a.result = result1->stack[result1->top];
    
    // Test 2: BOTTOM_A
    test_data.test2_bottom_a.input_array = malloc(size * sizeof(int));
    test_data.test2_bottom_a.array_size = size;
    test_data.test2_bottom_a.stack_loc = BOTTOM_A;
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test2_bottom_a.input_array[i] = data->a.stack[i];
    }
    
    // Run test
    t_stack *result2 = loc_to_stack(data, BOTTOM_A);
    test_data.test2_bottom_a.result = result2->stack[result2->bottom];
    
    // Test 3: TOP_B
    test_data.test3_top_b.input_array = malloc(size * sizeof(int));
    test_data.test3_top_b.array_size = size;
    test_data.test3_top_b.stack_loc = TOP_B;
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test3_top_b.input_array[i] = data->b.stack[i];
    }
    
    // Run test
    t_stack *result3 = loc_to_stack(data, TOP_B);
    test_data.test3_top_b.result = result3->stack[result3->top];
    
    // Test 4: BOTTOM_B
    test_data.test4_bottom_b.input_array = malloc(size * sizeof(int));
    test_data.test4_bottom_b.array_size = size;
    test_data.test4_bottom_b.stack_loc = BOTTOM_B;
    
    // Copy input data
    for (int i = 0; i < size; i++) {
        test_data.test4_bottom_b.input_array[i] = data->b.stack[i];
    }
    
    // Run test
    t_stack *result4 = loc_to_stack(data, BOTTOM_B);
    test_data.test4_bottom_b.result = result4->stack[result4->bottom];
    
    // Save results to JSON file
    save_loc_to_stack_results(data, &test_data);
    
    // Cleanup test data
    free(test_data.test1_top_a.input_array);
    free(test_data.test2_bottom_a.input_array);
    free(test_data.test3_top_b.input_array);
    free(test_data.test4_bottom_b.input_array);

    // Cleanup only once at the end
    cleanup_test_data(data);

    return 0;
}
