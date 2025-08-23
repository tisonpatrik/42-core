#include "../../../../include/chunk_max_value_test.h"
#include "../../../../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new chunk max value test
t_chunk_max_value_test* create_chunk_max_value_test(int id, const char *name, int *input_array, int array_size, int result, const char *chunk_loc, int chunk_size) {
    t_chunk_max_value_test *test = malloc(sizeof(t_chunk_max_value_test));
    if (!test) return NULL;
    
    test->id = id;
    test->name = strdup(name);
    test->array_size = array_size;
    test->result = result;
    test->chunk_loc = strdup(chunk_loc);
    test->chunk_size = chunk_size;
    
    // Allocate and copy input array
    test->input_array = malloc(array_size * sizeof(int));
    if (!test->input_array) {
        free(test->name);
        free(test->chunk_loc);
        free(test);
        return NULL;
    }
    memcpy(test->input_array, input_array, array_size * sizeof(int));
    
    return test;
}

// Free a chunk max value test
void free_chunk_max_value_test(t_chunk_max_value_test *test) {
    if (!test) return;
    
    free(test->name);
    free(test->chunk_loc);
    free(test->input_array);
    free(test);
}

// Save chunk max value tests to JSON file
void save_chunk_max_value_tests_to_json(t_chunk_max_value_test **tests, int num_tests, const char *filename) {
    cJSON *root = cJSON_CreateObject();
    cJSON *tests_array = cJSON_CreateArray();
    
    for (int i = 0; i < num_tests; i++) {
        if (!tests[i]) continue;
        
        cJSON *test_obj = cJSON_CreateObject();
        cJSON *input_array = cJSON_CreateArray();
        
        // Add test metadata
        cJSON_AddNumberToObject(test_obj, "id", tests[i]->id);
        cJSON_AddStringToObject(test_obj, "name", tests[i]->name);
        cJSON_AddNumberToObject(test_obj, "result", tests[i]->result);
        cJSON_AddStringToObject(test_obj, "chunk_loc", tests[i]->chunk_loc);
        cJSON_AddNumberToObject(test_obj, "chunk_size", tests[i]->chunk_size);
        
        // Add input array
        for (int j = 0; j < tests[i]->array_size; j++) {
            cJSON_AddItemToArray(input_array, cJSON_CreateNumber(tests[i]->input_array[j]));
        }
        cJSON_AddItemToObject(test_obj, "input_array", input_array);
        
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
    }
    
    cJSON_Delete(root);
}
