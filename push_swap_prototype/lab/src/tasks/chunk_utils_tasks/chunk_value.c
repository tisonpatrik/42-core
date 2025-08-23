#include "../../../libs/push_swap/src/models.h"
#include "../../../include/json_utils.h"
#include "../../../include/chunk_utils_task.h"
#include "../../../include/chunk_utils_common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    
    // Save to JSON file in chunk_utils directory
    save_chunk_utils_test_results("chunk_value", export_data);
    
    // Cleanup
    cleanup_json_export(export_data);
}

// Example implementation of chunk_value test
int run_chunk_value_tests(int size) {
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
