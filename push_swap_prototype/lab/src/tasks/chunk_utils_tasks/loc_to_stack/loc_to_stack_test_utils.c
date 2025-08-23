#include "../../../../include/loc_to_stack_test.h"
#include "../../../../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new loc to stack test
t_loc_to_stack_test* create_loc_to_stack_test(int id, const char *name, int *input_array, int array_size, int result, const char *stack_loc) {
    t_loc_to_stack_test *test = malloc(sizeof(t_loc_to_stack_test));
    if (!test) return NULL;
    
    test->id = id;
    test->name = strdup(name);
    test->array_size = array_size;
    test->result = result;
    test->stack_loc = strdup(stack_loc);
    
    // Allocate and copy input array
    test->input_array = malloc(array_size * sizeof(int));
    if (!test->input_array) {
        free(test->name);
        free(test->stack_loc);
        free(test);
        return NULL;
    }
    memcpy(test->input_array, input_array, array_size * sizeof(int));
    
    return test;
}

// Free a loc to stack test
void free_loc_to_stack_test(t_loc_to_stack_test *test) {
    if (!test) return;
    
    free(test->name);
    free(test->stack_loc);
    free(test->input_array);
    free(test);
}

// Save loc to stack tests to JSON file
void save_loc_to_stack_tests_to_json(t_loc_to_stack_test **tests, int num_tests, const char *filename) {
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
        cJSON_AddStringToObject(test_obj, "stack_loc", tests[i]->stack_loc);
        
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
