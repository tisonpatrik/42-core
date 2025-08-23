#include "../../include/json_utils.h"
#include "../../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>

// Generic function to save any test array to JSON
int save_tests_to_json_generic(const char *filename, const char *test_type, 
                               void **tests, int num_tests, 
                               void (*add_test_data)(void *test_obj, void *test)) {
    (void)test_type; // Suppress unused parameter warning
    if (!filename || !tests || !add_test_data) return 0;
    
    cJSON *root = cJSON_CreateObject();
    cJSON *tests_array = cJSON_CreateArray();
    
    for (int i = 0; i < num_tests; i++) {
        if (!tests[i]) continue;
        
        cJSON *test_obj = cJSON_CreateObject();
        
        // Add test-specific data using the callback function
        add_test_data((void*)test_obj, tests[i]);
        
        cJSON_AddItemToArray(tests_array, test_obj);
    }
    
    cJSON_AddItemToObject(root, "tests", tests_array);
    
    // Write to file in data/chunk_utils directory
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/chunk_utils/%s", filename);
    FILE *file = fopen(filepath, "w");
    if (file) {
        char *json_string = cJSON_Print(root);
        fprintf(file, "%s", json_string);
        free(json_string);
        fclose(file);
        return 1;
    }
    
    cJSON_Delete(root);
    return 0;
}

// Helper function to add input array to JSON
void add_input_array_to_json(void *test_obj, int *input_array, int array_size) {
    if (!test_obj || !input_array) return;
    
    cJSON *input_array_json = cJSON_CreateArray();
    for (int j = 0; j < array_size; j++) {
        cJSON_AddItemToArray(input_array_json, cJSON_CreateNumber(input_array[j]));
    }
    cJSON_AddItemToObject((cJSON*)test_obj, "input_array", input_array_json);
}
