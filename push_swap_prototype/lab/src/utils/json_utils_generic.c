#include "../../include/chunk_utils_task.h"
#include "../../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>

// Generic function to save test batch to JSON - NO MORE SPAGHETTI CODE!
void save_test_batch_to_json(t_test_batch *batch, const char *filename) {
    if (!batch || !filename) return;
    
    cJSON *root = cJSON_CreateArray();
    if (!root) return;
    
    // Iterate through all tests in the batch
    for (int i = 0; i < batch->num_tests; i++) {
        t_test_case *test = &batch->tests[i];
        
        cJSON *test_obj = cJSON_CreateObject();
        cJSON_AddItemToObject(test_obj, "id", cJSON_CreateNumber(test->id));
        cJSON_AddItemToObject(test_obj, "name", cJSON_CreateString(test->name));
        
        // Create inputs object
        cJSON *inputs = cJSON_CreateObject();
        
        // Add array
        cJSON *array = cJSON_CreateArray();
        for (int j = 0; j < test->array_size; j++) {
            cJSON_AddItemToArray(array, cJSON_CreateNumber(test->input_array[j]));
        }
        cJSON_AddItemToObject(inputs, "array", array);
        
        // Add optional parameters dynamically
        if (test->param1_name && test->param1_value) {
            cJSON_AddItemToObject(inputs, test->param1_name, cJSON_CreateString(test->param1_value));
        }
        
        if (test->param2_name) {
            cJSON_AddItemToObject(inputs, test->param2_name, cJSON_CreateNumber(test->param2_value));
        }
        
        if (test->param3_name && test->param3_value) {
            cJSON_AddItemToObject(inputs, test->param3_name, cJSON_CreateString(test->param3_value));
        }
        
        cJSON_AddItemToObject(test_obj, "inputs", inputs);
        cJSON_AddItemToObject(test_obj, "result", cJSON_CreateNumber(test->result));
        
        cJSON_AddItemToArray(root, test_obj);
    }
    
    // Convert to string and save to file
    char *json_string = cJSON_Print(root);
    if (!json_string) {
        cJSON_Delete(root);
        return;
    }
    
    // Create directory if it doesn't exist
    system("mkdir -p data/chunk_utils");
    
    // Save to file
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/chunk_utils/%s", filename);
    
    FILE *file = fopen(filepath, "w");
    if (file) {
        fprintf(file, "%s", json_string);
        fclose(file);
        printf("Results saved to: %s\n", filepath);
    } else {
        printf("Failed to save results to file: %s\n", filepath);
    }
    
    // Cleanup
    free(json_string);
    cJSON_Delete(root);
}
