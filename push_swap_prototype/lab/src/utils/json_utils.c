#include "../../include/utils/json_utils.h"
#include "../../include/testing/chunk_value_test.h"
#include "../../include/testing/chunk_max_value_test.h"
#include "../../include/testing/loc_to_stack_test.h"
#include "../../include/chunk_split_test.h"
#include "../../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Simple JSON writer - no complex callbacks needed
int save_tests_to_json_generic(const char *filename, const char *test_type, 
                               void **tests, int num_tests, 
                               void (*add_test_data)(void *test_obj, void *test)) {
    (void)test_type; // Suppress unused parameter warning
    
    cJSON *json_root = cJSON_CreateObject();
    cJSON *json_tests_array = cJSON_CreateArray();
    
    for (int i = 0; i < num_tests; i++) {
        if (!tests[i]) continue;
        
        cJSON *test_obj = cJSON_CreateObject();
        add_test_data(test_obj, tests[i]);
        cJSON_AddItemToArray(json_tests_array, test_obj);
    }
    
    cJSON_AddItemToObject(json_root, "tests", json_tests_array);
    
    // Write to file
    char filepath[512];
    char dirpath[256];
    
    // Determine the correct directory based on test type
    if (strstr(test_type, "chunk_split") != NULL) {
        snprintf(dirpath, sizeof(dirpath), "data/chunk_split");
        snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, filename);
    } else {
        snprintf(dirpath, sizeof(dirpath), "data/chunk_utils");
        snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, filename);
    }
    
    // Create directory if it doesn't exist
    #ifdef _WIN32
    _mkdir(dirpath);
    #else
    mkdir(dirpath, 0755);
    #endif
    
    FILE *file = fopen(filepath, "w");
    if (file) {
        char *json_str = cJSON_Print(json_root);
        fprintf(file, "%s", json_str);
        free(json_str);
        fclose(file);
        cJSON_Delete(json_root);
        return 0;
    }
    
    cJSON_Delete(json_root);
    return 1;
}

// Simple test data adders - direct JSON creation
void add_chunk_value_test_data(void *json_obj, void *test) {
    t_chunk_value_test *t = (t_chunk_value_test*)test;
    cJSON *obj = (cJSON*)json_obj;
    
    cJSON_AddNumberToObject(obj, "id", t->id);
    cJSON_AddStringToObject(obj, "name", t->name);
    cJSON_AddNumberToObject(obj, "result", t->result);
    cJSON_AddStringToObject(obj, "chunk_loc", t->chunk_loc);
    cJSON_AddNumberToObject(obj, "chunk_size", t->chunk_size);
    cJSON_AddNumberToObject(obj, "offset", t->offset);
    
    // Add input array
    cJSON *array = cJSON_CreateArray();
    for (int i = 0; i < t->array_size; i++) {
        cJSON_AddItemToArray(array, cJSON_CreateNumber(t->input_array[i]));
    }
    cJSON_AddItemToObject(obj, "input_array", array);
}

void add_chunk_max_value_test_data(void *json_obj, void *test) {
    t_chunk_max_value_test *t = (t_chunk_max_value_test*)test;
    cJSON *obj = (cJSON*)json_obj;
    
    cJSON_AddNumberToObject(obj, "id", t->id);
    cJSON_AddStringToObject(obj, "name", t->name);
    cJSON_AddNumberToObject(obj, "result", t->result);
    cJSON_AddStringToObject(obj, "chunk_loc", t->chunk_loc);
    cJSON_AddNumberToObject(obj, "chunk_size", t->chunk_size);
    
    // Add input array
    cJSON *array = cJSON_CreateArray();
    for (int i = 0; i < t->array_size; i++) {
        cJSON_AddItemToArray(array, cJSON_CreateNumber(t->input_array[i]));
    }
    cJSON_AddItemToObject(obj, "input_array", array);
}

void add_loc_to_stack_test_data(void *json_obj, void *test) {
    t_loc_to_stack_test *t = (t_loc_to_stack_test*)test;
    cJSON *obj = (cJSON*)json_obj;
    
    cJSON_AddNumberToObject(obj, "id", t->id);
    cJSON_AddStringToObject(obj, "name", t->name);
    cJSON_AddNumberToObject(obj, "result", t->result);
    cJSON_AddStringToObject(obj, "stack_loc", t->stack_loc);
    
    // Add input array
    cJSON *array = cJSON_CreateArray();
    for (int i = 0; i < t->array_size; i++) {
        cJSON_AddItemToArray(array, cJSON_CreateNumber(t->input_array[i]));
    }
    cJSON_AddItemToObject(obj, "input_array", array);
}

// Chunk split test data adders
void add_chunk_split_test_data(void *json_obj, void *test) {
    t_chunk_split_test *t = (t_chunk_split_test*)test;
    cJSON *obj = (cJSON*)json_obj;
    
    cJSON_AddNumberToObject(obj, "id", t->id);
    cJSON_AddStringToObject(obj, "name", t->name);
    cJSON_AddNumberToObject(obj, "original_chunk_size", t->original_chunk_size);
    cJSON_AddStringToObject(obj, "original_chunk_loc", t->original_chunk_loc);
    cJSON_AddNumberToObject(obj, "min_size_result", t->min_size_result);
    cJSON_AddNumberToObject(obj, "mid_size_result", t->mid_size_result);
    cJSON_AddNumberToObject(obj, "max_size_result", t->max_size_result);
    cJSON_AddStringToObject(obj, "min_loc_result", t->min_loc_result);
    cJSON_AddStringToObject(obj, "mid_loc_result", t->mid_loc_result);
    cJSON_AddStringToObject(obj, "max_loc_result", t->max_loc_result);
    
    // Add input array
    cJSON *array = cJSON_CreateArray();
    for (int i = 0; i < t->array_size; i++) {
        cJSON_AddItemToArray(array, cJSON_CreateNumber(t->input_array[i]));
    }
    cJSON_AddItemToObject(obj, "input_array", array);
}
