#include "../../include/chunk_utils_task.h"
#include "../../include/specific_test_utils.h"
#include "../../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>

// Save chunk max value tests to JSON
void save_chunk_max_value_tests_to_json(t_chunk_max_value_test **tests, int num_tests, const char *filename) {
    cJSON *root = cJSON_CreateObject();
    cJSON *test_array = cJSON_CreateArray();
    
    cJSON_AddItemToObject(root, "test_type", cJSON_CreateString("chunk_max_value"));
    cJSON_AddItemToObject(root, "num_tests", cJSON_CreateNumber(num_tests));
    cJSON_AddItemToObject(root, "tests", test_array);
    
    for (int i = 0; i < num_tests; i++) {
        if (!tests[i]) continue;
        
        cJSON *test_obj = cJSON_CreateObject();
        cJSON_AddItemToObject(test_obj, "id", cJSON_CreateNumber(tests[i]->id));
        cJSON_AddItemToObject(test_obj, "name", cJSON_CreateString(tests[i]->name));
        cJSON_AddItemToObject(test_obj, "result", cJSON_CreateNumber(tests[i]->result));
        
        // Input array
        if (tests[i]->input_array && tests[i]->array_size > 0) {
            cJSON *array = cJSON_CreateArray();
            for (int j = 0; j < tests[i]->array_size; j++) {
                cJSON_AddItemToArray(array, cJSON_CreateNumber(tests[i]->input_array[j]));
            }
            cJSON_AddItemToObject(test_obj, "input_array", array);
        }
        
        // Test parameters
        cJSON *inputs = cJSON_CreateObject();
        cJSON_AddItemToObject(inputs, "chunk_loc", cJSON_CreateString(tests[i]->chunk_loc));
        cJSON_AddItemToObject(inputs, "chunk_size", cJSON_CreateNumber(tests[i]->chunk_size));
        cJSON_AddItemToObject(test_obj, "inputs", inputs);
        
        cJSON_AddItemToArray(test_array, test_obj);
    }
    
    char *json_string = cJSON_Print(root);
    if (json_string) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "data/chunk_utils/%s", filename);
        
        // Ensure directory exists
        system("mkdir -p data/chunk_utils");
        
        // Save to file
        FILE *file = fopen(filepath, "w");
        if (file) {
            fprintf(file, "%s", json_string);
            fclose(file);
            printf("Results saved to: %s\n", filepath);
        } else {
            printf("Failed to save results to file: %s\n", filepath);
        }
        
        free(json_string);
    }
    
    cJSON_Delete(root);
}

// Save chunk value tests to JSON
void save_chunk_value_tests_to_json(t_chunk_value_test **tests, int num_tests, const char *filename) {
    cJSON *root = cJSON_CreateObject();
    cJSON *test_array = cJSON_CreateArray();
    
    cJSON_AddItemToObject(root, "test_type", cJSON_CreateString("chunk_value"));
    cJSON_AddItemToObject(root, "num_tests", cJSON_CreateNumber(num_tests));
    cJSON_AddItemToObject(root, "tests", test_array);
    
    for (int i = 0; i < num_tests; i++) {
        if (!tests[i]) continue;
        
        cJSON *test_obj = cJSON_CreateObject();
        cJSON_AddItemToObject(test_obj, "id", cJSON_CreateNumber(tests[i]->id));
        cJSON_AddItemToObject(test_obj, "name", cJSON_CreateString(tests[i]->name));
        cJSON_AddItemToObject(test_obj, "result", cJSON_CreateNumber(tests[i]->result));
        
        // Input array
        if (tests[i]->input_array && tests[i]->array_size > 0) {
            cJSON *array = cJSON_CreateArray();
            for (int j = 0; j < tests[i]->array_size; j++) {
                cJSON_AddItemToArray(array, cJSON_CreateNumber(tests[i]->input_array[j]));
            }
            cJSON_AddItemToObject(test_obj, "input_array", array);
        }
        
        // Test parameters
        cJSON *inputs = cJSON_CreateObject();
        cJSON_AddItemToObject(inputs, "chunk_loc", cJSON_CreateString(tests[i]->chunk_loc));
        cJSON_AddItemToObject(inputs, "chunk_size", cJSON_CreateNumber(tests[i]->chunk_size));
        cJSON_AddItemToObject(inputs, "offset", cJSON_CreateNumber(tests[i]->offset));
        cJSON_AddItemToObject(test_obj, "inputs", inputs);
        
        cJSON_AddItemToArray(test_array, test_obj);
    }
    
    char *json_string = cJSON_Print(root);
    if (json_string) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "data/chunk_utils/%s", filename);
        
        // Ensure directory exists
        system("mkdir -p data/chunk_utils");
        
        // Save to file
        FILE *file = fopen(filepath, "w");
        if (file) {
            fprintf(file, "%s", json_string);
            fclose(file);
            printf("Results saved to: %s\n", filepath);
        } else {
            printf("Failed to save results to file: %s\n", filepath);
        }
        
        free(json_string);
    }
    
    cJSON_Delete(root);
}

// Save loc to stack tests to JSON
void save_loc_to_stack_tests_to_json(t_loc_to_stack_test **tests, int num_tests, const char *filename) {
    cJSON *root = cJSON_CreateObject();
    cJSON *test_array = cJSON_CreateArray();
    
    cJSON_AddItemToObject(root, "test_type", cJSON_CreateString("loc_to_stack"));
    cJSON_AddItemToObject(root, "num_tests", cJSON_CreateNumber(num_tests));
    cJSON_AddItemToObject(root, "tests", test_array);
    
    for (int i = 0; i < num_tests; i++) {
        if (!tests[i]) continue;
        
        cJSON *test_obj = cJSON_CreateObject();
        cJSON_AddItemToObject(test_obj, "id", cJSON_CreateNumber(tests[i]->id));
        cJSON_AddItemToObject(test_obj, "name", cJSON_CreateString(tests[i]->name));
        cJSON_AddItemToObject(test_obj, "result", cJSON_CreateNumber(tests[i]->result));
        
        // Input array
        if (tests[i]->input_array && tests[i]->array_size > 0) {
            cJSON *array = cJSON_CreateArray();
            for (int j = 0; j < tests[i]->array_size; j++) {
                cJSON_AddItemToArray(array, cJSON_CreateNumber(tests[i]->input_array[j]));
            }
            cJSON_AddItemToObject(test_obj, "input_array", array);
        }
        
        // Test parameters
        cJSON *inputs = cJSON_CreateObject();
        cJSON_AddItemToObject(inputs, "stack_loc", cJSON_CreateString(tests[i]->stack_loc));
        cJSON_AddItemToObject(test_obj, "inputs", inputs);
        
        cJSON_AddItemToArray(test_array, test_obj);
    }
    
    char *json_string = cJSON_Print(root);
    if (json_string) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "data/chunk_utils/%s", filename);
        
        // Ensure directory exists
        system("mkdir -p data/chunk_utils");
        
        // Save to file
        FILE *file = fopen(filepath, "w");
        if (file) {
            fprintf(file, "%s", json_string);
            fclose(file);
            printf("Results saved to: %s\n", filepath);
        } else {
            printf("Failed to save results to file: %s\n", filepath);
        }
        
        free(json_string);
    }
    
    cJSON_Delete(root);
}
