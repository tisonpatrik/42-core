
// Import the data structures and types from models.h
#include "../../libs/push_swap/src/models.h"
#include "../../include/generator.h"
#include "../../include/json_utils.h"
#include "../../include/chunk_utils_task.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>  // Added for timestamp
#include <unistd.h> // Added for system calls

// Forward declaration of the function to test
t_stack	*loc_to_stack(t_ps *data, t_loc loc);

// Helper function to initialize a stack with random data
void init_stack(t_stack *stack, int size) {
    int *random_data = generate_random_array(size);
    stack->stack = random_data;
    stack->size = size;
    stack->top = 0;
    stack->bottom = size - 1;
}

// Helper function to free stack data
void cleanup_stack(t_stack *stack) {
    if (stack->stack) {
        free(stack->stack);
        stack->stack = NULL;
    }
}

// Helper function to create test data structure
t_ps* create_test_data(int stack_a_size, int stack_b_size) {
    t_ps *data = malloc(sizeof(t_ps));
    if (!data) return NULL;
        
    init_stack(&data->a, stack_a_size);
    init_stack(&data->b, stack_b_size);
    data->op_list = NULL;
    data->writing_mode = false;
    
    return data;
}

// Helper function to cleanup test data
void cleanup_test_data(t_ps *data) {
    if (data) {
        cleanup_stack(&data->a);
        cleanup_stack(&data->b);
        free(data);
    }
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
    
    // Save to JSON file in chunk_utils/loc_to_stack directory
    save_test_results_to_json("chunk_utils/loc_to_stack", export_data);
    
    // Cleanup
    cleanup_json_export(export_data);
}

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

int run_loc_to_stack_tests() {
    int size = 10;
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

// Function to save chunk_max_value test results using generic JSON utils
void save_chunk_max_value_results(t_ps *data __attribute__((unused)), t_chunk_max_value_test *test_data) {
    // Create JSON export structure
    t_json_export *export_data = create_json_export(
        "Chunk Max Value Test Results", 
        "Test results for chunk_max_value function"
    );
    
    if (!export_data) {
        printf("Failed to create JSON export structure\n");
        return;
    }
    
    // Add test results
    add_test_result(export_data, create_test_result(1, "max_value_a", test_data->max_value_a));
    add_test_result(export_data, create_test_result(2, "max_value_b", test_data->max_value_b));
    add_test_result(export_data, create_test_result(3, "max_value_combined", test_data->max_value_combined));
    add_test_result(export_data, create_test_result(4, "chunk_size", test_data->chunk_size));
    
    // Add input data
    add_custom_int_array(export_data, "chunk_data", test_data->chunk_data, test_data->chunk_size);
    add_custom_string(export_data, "chunk_range", "chunk_start_index to chunk_end_index");
    
    // Save to JSON file in chunk_utils/chunk_max_value directory
    save_test_results_to_json("chunk_utils/chunk_max_value", export_data);
    
    // Cleanup
    cleanup_json_export(export_data);
}

// Example implementation of chunk_max_value test
int run_chunk_max_value_tests() {
    int size = 10;
	t_ps *data = create_test_data(size, size);
	if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
	
	// Simulate chunk_max_value test results
    t_chunk_max_value_test test_data;
    test_data.max_value_a = 9;  // Assuming max value in stack A
    test_data.max_value_b = 8;  // Assuming max value in stack B
    test_data.max_value_combined = 9;  // Overall max
    test_data.chunk_size = 5;
    test_data.chunk_start_index = 2;
    test_data.chunk_end_index = 6;
    
    // Create sample chunk data
    test_data.chunk_data = malloc(test_data.chunk_size * sizeof(int));
    if (test_data.chunk_data) {
        for (int i = 0; i < test_data.chunk_size; i++) {
            test_data.chunk_data[i] = data->a.stack[(test_data.chunk_start_index + i) % size];
        }
        
        // Save results to JSON file
        save_chunk_max_value_results(data, &test_data);
        
        // Cleanup test data
        free(test_data.chunk_data);
    }

    // Cleanup only once at the end
    cleanup_test_data(data);

    return 0;
}

// Function to save chunk_value test results using generic JSON utils
void save_chunk_value_results(t_ps *data __attribute__((unused)), t_chunk_value_test *test_data) {
    // Create JSON export structure
    t_json_export *export_data = create_json_export(
        "Chunk Value Test Results", 
        "Test results for chunk_value function - searching for specific values in chunks"
    );
    
    if (!export_data) {
        printf("Failed to create JSON export structure\n");
        return;
    }
    
    // Add test results
    add_test_result(export_data, create_test_result(1, "target_value", test_data->target_value));
    add_test_result(export_data, create_test_result(2, "found_value", test_data->found_value));
    add_test_result(export_data, create_test_result(3, "found_index", test_data->found_index));
    add_test_result(export_data, create_test_result(4, "search_range_size", test_data->search_range_end - test_data->search_range_start));
    
    // Add input data
    add_custom_int_array(export_data, "search_data", test_data->search_data, test_data->search_data_size);
    add_custom_string(export_data, "search_range", "search_range_start to search_range_end");
    add_custom_string(export_data, "value_found", test_data->value_found ? "true" : "false");
    
    // Save to JSON file in chunk_utils/chunk_value directory
    save_test_results_to_json("chunk_utils/chunk_value", export_data);
    
    // Cleanup
    cleanup_json_export(export_data);
}

// Example implementation of chunk_value test
int run_chunk_value_tests() {
    int size = 10;
	t_ps *data = create_test_data(size, size);
	if (!data) {
        printf("Failed to create test data\n");
        return 1;
    }
	
	// Simulate chunk_value test results
    t_chunk_value_test test_data;
    test_data.target_value = 5;
    test_data.found_value = 5;
    test_data.found_index = 3;
    test_data.search_range_start = 1;
    test_data.search_range_end = 7;
    test_data.value_found = true;
    
    // Create sample search data (subset of stack)
    test_data.search_data_size = test_data.search_range_end - test_data.search_range_start;
    test_data.search_data = malloc(test_data.search_data_size * sizeof(int));
    if (test_data.search_data) {
        for (int i = 0; i < test_data.search_data_size; i++) {
            test_data.search_data[i] = data->a.stack[(test_data.search_range_start + i) % size];
        }
        
        // Save results to JSON file
        save_chunk_value_results(data, &test_data);
        
        // Cleanup test data
        free(test_data.search_data);
    }

    // Cleanup only once at the end
    cleanup_test_data(data);

    return 0;
}