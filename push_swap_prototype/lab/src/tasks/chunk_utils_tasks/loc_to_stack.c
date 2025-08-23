#include "../../../libs/push_swap/src/models.h"
#include "../../../include/json_utils.h"
#include "../../../include/chunk_utils_task.h"
#include "../../../include/chunk_utils_common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Forward declaration of the function to test
t_stack	*loc_to_stack(t_ps *data, t_loc loc);

// Modified test functions to return results instead of printing
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

// Function to save loc_to_stack test results using generic JSON utils
void save_loc_to_stack_results(t_ps *data __attribute__((unused)), t_loc_to_stack_test *test_data) {
    // Create JSON export structure
    t_json_export *export_data = create_json_export(
        "Loc to Stack Test Results", 
        "Test results for loc_to_stack function with different locations"
    );
    
    if (!export_data) {
        printf("Failed to create JSON export structure\n");
        return;
    }
    
    // Add test results
    const char *locations[] = {"TOP_A", "BOTTOM_A", "TOP_B", "BOTTOM_B"};
    int results[] = {test_data->top_a_result, test_data->bottom_a_result, 
                     test_data->top_b_result, test_data->bottom_b_result};
    
    for (int i = 0; i < 4; i++) {
        t_test_result result = create_test_result(i + 1, locations[i], results[i]);
        add_test_result(export_data, result);
    }
    
    // Add input data - stack contents
    add_custom_int_array(export_data, "stack_a", test_data->stack_a_data, test_data->stack_a_size);
    add_custom_int_array(export_data, "stack_b", test_data->stack_b_data, test_data->stack_b_size);
    
    // Save to JSON file in chunk_utils directory
    save_chunk_utils_test_results("loc_to_stack", export_data);
    
    // Cleanup
    cleanup_json_export(export_data);
}

// Main function to run loc_to_stack tests
int run_loc_to_stack_tests(int size) {
	t_ps *data = create_test_data(size, size);
	if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
	
	// Run tests and collect results
    t_loc_to_stack_test test_data;
    test_data.top_a_result = test_loc_to_stack_top_a(data);
    test_data.bottom_a_result = test_loc_to_stack_bottom_a(data);
    test_data.top_b_result = test_loc_to_stack_top_b(data);
    test_data.bottom_b_result = test_loc_to_stack_bottom_b(data);
    
    // Copy stack data for JSON export
    test_data.stack_a_data = malloc(size * sizeof(int));
    test_data.stack_b_data = malloc(size * sizeof(int));
    if (test_data.stack_a_data && test_data.stack_b_data) {
        for (int i = 0; i < size; i++) {
            test_data.stack_a_data[i] = data->a.stack[i];
            test_data.stack_b_data[i] = data->b.stack[i];
        }
        test_data.stack_a_size = size;
        test_data.stack_b_size = size;
        
        // Save results to JSON file
        save_loc_to_stack_results(data, &test_data);
        
        // Cleanup test data
        free(test_data.stack_a_data);
        free(test_data.stack_b_data);
    }

    // Cleanup only once at the end
    cleanup_test_data(data);

    return 0;
}
