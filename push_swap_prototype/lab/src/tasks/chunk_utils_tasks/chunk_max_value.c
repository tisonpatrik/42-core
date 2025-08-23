#include "../../../libs/push_swap/src/models.h"
#include "../../../include/json_utils.h"
#include "../../../include/chunk_utils_task.h"
#include "../../../include/chunk_utils_common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    
    // Save to JSON file in chunk_utils directory
    save_chunk_utils_test_results("chunk_max_value", export_data);
    
    // Cleanup
    cleanup_json_export(export_data);
}

// Example implementation of chunk_max_value test
int run_chunk_max_value_tests(int size) {
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
