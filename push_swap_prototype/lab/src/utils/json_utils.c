#include "../../include/json_utils.h"
#include "../../include/chunk_value_test.h"
#include "../../include/chunk_max_value_test.h"
#include "../../include/loc_to_stack_test.h"
#include "../../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>

// Constants for file operations
#define MAX_FILEPATH_LENGTH 256

// Generic function to save any test array to JSON
int save_tests_to_json_generic(const char *filename, const char *test_type, 
                               void **tests, int num_tests, 
                               void (*add_test_data)(void *test_obj, void *test)) {
    (void)test_type; // Suppress unused parameter warning
    RETURN_IF_NULL(filename);
    RETURN_IF_NULL(tests);
    RETURN_IF_NULL(add_test_data);
    
    cJSON *json_root = cJSON_CreateObject();
    cJSON *json_tests_array = cJSON_CreateArray();
    
    for (int test_index = 0; test_index < num_tests; test_index++) {
        if (!tests[test_index]) continue;
        
        cJSON *current_test_obj = cJSON_CreateObject();
        
        // Add test-specific data using the callback function
        add_test_data((void*)current_test_obj, tests[test_index]);
        
        cJSON_AddItemToArray(json_tests_array, current_test_obj);
    }
    
    cJSON_AddItemToObject(json_root, "tests", json_tests_array);
    
    // Write to file in data/chunk_utils directory
    char output_filepath[MAX_FILEPATH_LENGTH];
    snprintf(output_filepath, sizeof(output_filepath), "data/chunk_utils/%s", filename);
    FILE *output_file = fopen(output_filepath, "w");
    if (output_file) {
        char *formatted_json_string = cJSON_Print(json_root);
        fprintf(output_file, "%s", formatted_json_string);
        free(formatted_json_string);
        fclose(output_file);
        cJSON_Delete(json_root);
        RETURN_SUCCESS;
    }
    
    cJSON_Delete(json_root);
    RETURN_FAILURE;
}

// Helper function to add input array to JSON
void add_input_array_to_json(void *json_test_obj, int *input_array, int array_size) {
    if (!json_test_obj || !input_array) return;
    
    cJSON *json_input_array = cJSON_CreateArray();
    for (int element_index = 0; element_index < array_size; element_index++) {
        cJSON_AddItemToArray(json_input_array, cJSON_CreateNumber(input_array[element_index]));
    }
    cJSON_AddItemToObject((cJSON*)json_test_obj, "input_array", json_input_array);
}

// Callback function for chunk value tests
void add_chunk_value_test_data(void *json_test_obj, void *chunk_value_test) {
    if (!json_test_obj || !chunk_value_test) return;
    
    t_chunk_value_test *current_chunk_test = (t_chunk_value_test*)chunk_value_test;
    cJSON *json_test_object = (cJSON*)json_test_obj;
    
    // Add test metadata
    cJSON_AddNumberToObject(json_test_object, "id", current_chunk_test->id);
    cJSON_AddStringToObject(json_test_object, "name", current_chunk_test->name);
    cJSON_AddNumberToObject(json_test_object, "result", current_chunk_test->result);
    cJSON_AddStringToObject(json_test_object, "chunk_loc", current_chunk_test->chunk_loc);
    cJSON_AddNumberToObject(json_test_object, "chunk_size", current_chunk_test->chunk_size);
    cJSON_AddNumberToObject(json_test_object, "offset", current_chunk_test->offset);
    
    // Add input array
    add_input_array_to_json(json_test_obj, current_chunk_test->input_array, current_chunk_test->array_size);
}

// Callback function for chunk max value tests
void add_chunk_max_value_test_data(void *json_test_obj, void *chunk_max_value_test) {
    if (!json_test_obj || !chunk_max_value_test) return;
    
    t_chunk_max_value_test *current_chunk_test = (t_chunk_max_value_test*)chunk_max_value_test;
    cJSON *json_test_object = (cJSON*)json_test_obj;
    
    // Add test metadata
    cJSON_AddNumberToObject(json_test_object, "id", current_chunk_test->id);
    cJSON_AddStringToObject(json_test_object, "name", current_chunk_test->name);
    cJSON_AddNumberToObject(json_test_object, "result", current_chunk_test->result);
    cJSON_AddStringToObject(json_test_object, "chunk_loc", current_chunk_test->chunk_loc);
    cJSON_AddNumberToObject(json_test_object, "chunk_size", current_chunk_test->chunk_size);
    
    // Add input array
    add_input_array_to_json(json_test_obj, current_chunk_test->input_array, current_chunk_test->array_size);
}

// Callback function for loc to stack tests
void add_loc_to_stack_test_data(void *json_test_obj, void *loc_to_stack_test) {
    if (!json_test_obj || !loc_to_stack_test) return;
    
    t_loc_to_stack_test *current_stack_test = (t_loc_to_stack_test*)loc_to_stack_test;
    cJSON *json_test_object = (cJSON*)json_test_obj;
    
    // Add test metadata
    cJSON_AddNumberToObject(json_test_object, "id", current_stack_test->id);
    cJSON_AddStringToObject(json_test_object, "name", current_stack_test->name);
    cJSON_AddNumberToObject(json_test_object, "result", current_stack_test->result);
    cJSON_AddStringToObject(json_test_object, "stack_loc", current_stack_test->stack_loc);
    
    // Add input array
    add_input_array_to_json(json_test_obj, current_stack_test->input_array, current_stack_test->array_size);
}
