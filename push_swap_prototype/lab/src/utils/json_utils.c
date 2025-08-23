#include "../../include/json_utils.h"
#include "../../include/chunk_utils_task.h"
#include "../../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Helper function to create test result
t_test_result create_test_result(int id, const char *name, int value) {
    t_test_result result;
    result.id = id;
    result.name = name;
    result.value = value;
    return result;
}

// Helper function to create JSON export structure
t_json_export *create_json_export(const char *title, const char *description) {
    t_json_export *export_data = malloc(sizeof(t_json_export));
    if (!export_data) return NULL;
    
    export_data->title = title;
    export_data->description = description;
    export_data->timestamp = time(NULL);
    export_data->num_results = 0;
    export_data->results = NULL;
    export_data->num_custom_data = 0;
    export_data->custom_data = NULL;
    
    return export_data;
}

// Helper function to add test result to export
int add_test_result(t_json_export *export_data, t_test_result result) {
    if (!export_data) return 0;
    
    t_test_result *new_results = realloc(export_data->results, 
                                        (export_data->num_results + 1) * sizeof(t_test_result));
    if (!new_results) return 0;
    
    export_data->results = new_results;
    export_data->results[export_data->num_results] = result;
    export_data->num_results++;
    
    return 1;
}

// Helper function to add custom data (array of integers)
int add_custom_int_array(t_json_export *export_data, const char *key, int *array, int size) {
    if (!export_data || !key || !array) return 0;
    
    t_custom_data *new_custom_data = realloc(export_data->custom_data,
                                            (export_data->num_custom_data + 1) * sizeof(t_custom_data));
    if (!new_custom_data) return 0;
    
    export_data->custom_data = new_custom_data;
    export_data->custom_data[export_data->num_custom_data].key = key;
    export_data->custom_data[export_data->num_custom_data].type = "array";
    export_data->custom_data[export_data->num_custom_data].value = array;
    export_data->custom_data[export_data->num_custom_data].size = size;
    export_data->num_custom_data++;
    
    return 1;
}

// Helper function to add custom data (string)
int add_custom_string(t_json_export *export_data, const char *key, const char *value) {
    if (!export_data || !key || !value) return 0;
    
    t_custom_data *new_custom_data = realloc(export_data->custom_data,
                                            (export_data->num_custom_data + 1) * sizeof(t_custom_data));
    if (!new_custom_data) return 0;
    
    export_data->custom_data = new_custom_data;
    export_data->custom_data[export_data->num_custom_data].key = key;
    export_data->custom_data[export_data->num_custom_data].type = "string";
    export_data->custom_data[export_data->num_custom_data].value = (void*)value;
    export_data->custom_data[export_data->num_custom_data].size = 0;
    export_data->num_custom_data++;
    
    return 1;
}

// Generic function to save test results to JSON
int save_test_results_to_json(const char *filename_prefix, t_json_export *export_data) {
    if (!export_data || !filename_prefix) return 0;
    
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;
    
    // Add metadata
    cJSON_AddItemToObject(root, "title", cJSON_CreateString(export_data->title));
    cJSON_AddItemToObject(root, "description", cJSON_CreateString(export_data->description));
    
    // Add test results
    cJSON *tests = cJSON_CreateArray();
    if (!tests) {
        cJSON_Delete(root);
        return 0;
    }
    
    for (int i = 0; i < export_data->num_results; i++) {
        cJSON *test = cJSON_CreateObject();
        if (!test) continue;
        
        cJSON_AddItemToObject(test, "id", cJSON_CreateNumber(export_data->results[i].id));
        cJSON_AddItemToObject(test, "name", cJSON_CreateString(export_data->results[i].name));
        cJSON_AddItemToObject(test, "result", cJSON_CreateNumber(export_data->results[i].value));
        
        cJSON_AddItemToArray(tests, test);
    }
    cJSON_AddItemToObject(root, "tests", tests);
    
    // Add input data
    if (export_data->num_custom_data > 0) {
        cJSON *input_data = cJSON_CreateObject();
        if (input_data) {
            for (int i = 0; i < export_data->num_custom_data; i++) {
                if (strcmp(export_data->custom_data[i].type, "array") == 0) {
                    cJSON *array = cJSON_CreateArray();
                    if (array) {
                        int *int_array = (int*)export_data->custom_data[i].value;
                        for (int j = 0; j < export_data->custom_data[i].size; j++) {
                            cJSON_AddItemToArray(array, cJSON_CreateNumber(int_array[j]));
                        }
                        cJSON_AddItemToObject(input_data, export_data->custom_data[i].key, array);
                    }
                } else if (strcmp(export_data->custom_data[i].type, "string") == 0) {
                    cJSON_AddItemToObject(input_data, export_data->custom_data[i].key, 
                                        cJSON_CreateString((char*)export_data->custom_data[i].value));
                }
            }
            cJSON_AddItemToObject(root, "input", input_data);
        }
    }
    
    // Convert to string and save to file
    char *json_string = cJSON_Print(root);
    if (!json_string) {
        cJSON_Delete(root);
        return 0;
    }
    
    // Create data directory if it doesn't exist
    char dir_path[256];
    snprintf(dir_path, sizeof(dir_path), "data/%s", filename_prefix);
    char mkdir_cmd[512];
    snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p %s", dir_path);
    system(mkdir_cmd);
    
    // Generate filename without timestamp - just the name
    char filename[512];
    
    // Extract just the filename part (last part after /)
    char *last_slash = strrchr(filename_prefix, '/');
    const char *file_part = last_slash ? last_slash + 1 : filename_prefix;
    snprintf(filename, sizeof(filename), "%s/%s.json", dir_path, file_part);
    
    FILE *file = fopen(filename, "w");
    int success = 0;
    if (file) {
        fprintf(file, "%s", json_string);
        fclose(file);
        printf("Results saved to: %s\n", filename);
        success = 1;
    } else {
        printf("Failed to save results to file\n");
    }
    
    // Cleanup
    free(json_string);
    cJSON_Delete(root);
    
    return success;
}

// Special function for chunk_utils tests - saves to chunk_utils directory with specific test name
int save_chunk_utils_test_results(const char *test_name, t_json_export *export_data) {
    if (!export_data || !test_name) return 0;
    
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;
    
    // Add metadata
    cJSON_AddItemToObject(root, "title", cJSON_CreateString(export_data->title));
    cJSON_AddItemToObject(root, "description", cJSON_CreateString(export_data->description));
    
    // Add test results
    cJSON *tests = cJSON_CreateArray();
    if (!tests) {
        cJSON_Delete(root);
        return 0;
    }
    
    for (int i = 0; i < export_data->num_results; i++) {
        cJSON *test = cJSON_CreateObject();
        if (!test) continue;
        
        cJSON_AddItemToObject(test, "id", cJSON_CreateNumber(export_data->results[i].id));
        cJSON_AddItemToObject(test, "name", cJSON_CreateString(export_data->results[i].name));
        cJSON_AddItemToObject(test, "result", cJSON_CreateNumber(export_data->results[i].value));
        
        cJSON_AddItemToArray(tests, test);
    }
    cJSON_AddItemToObject(root, "tests", tests);
    
    // Add input data
    if (export_data->num_custom_data > 0) {
        cJSON *input_data = cJSON_CreateObject();
        if (input_data) {
            for (int i = 0; i < export_data->num_custom_data; i++) {
                if (strcmp(export_data->custom_data[i].type, "array") == 0) {
                    cJSON *array = cJSON_CreateArray();
                    if (array) {
                        int *int_array = (int*)export_data->custom_data[i].value;
                        for (int j = 0; j < export_data->custom_data[i].size; j++) {
                            cJSON_AddItemToArray(array, cJSON_CreateNumber(int_array[j]));
                        }
                        cJSON_AddItemToObject(input_data, export_data->custom_data[i].key, array);
                    }
                } else if (strcmp(export_data->custom_data[i].type, "string") == 0) {
                    cJSON_AddItemToObject(input_data, export_data->custom_data[i].key, 
                                        cJSON_CreateString((char*)export_data->custom_data[i].value));
                }
            }
            cJSON_AddItemToObject(root, "input", input_data);
        }
    }
    
    // Convert to string and save to file
    char *json_string = cJSON_Print(root);
    if (!json_string) {
        cJSON_Delete(root);
        return 0;
    }
    
    // Create chunk_utils directory if it doesn't exist
    system("mkdir -p data/chunk_utils");
    
    // Generate filename with test name
    char filename[256];
    snprintf(filename, sizeof(filename), "data/chunk_utils/%s.json", test_name);
    
    FILE *file = fopen(filename, "w");
    int success = 0;
    if (file) {
        fprintf(file, "%s", json_string);
        fclose(file);
        printf("Results saved to: %s\n", filename);
        success = 1;
    } else {
        printf("Failed to save results to file\n");
    }
    
    // Cleanup
    free(json_string);
    cJSON_Delete(root);
    
    return success;
}

// Generic function to save test results with custom data
int save_generic_test_results(const char *test_name, 
                             const char *title, 
                             const char *description,
                             t_test_result *results, 
                             int num_results,
                             t_custom_data *custom_data, 
                             int num_custom_data) {
    
    t_json_export *export_data = create_json_export(title, description);
    if (!export_data) {
        printf("Failed to create JSON export structure\n");
        return 0;
    }
    
    // Add all test results
    for (int i = 0; i < num_results; i++) {
        if (!add_test_result(export_data, results[i])) {
            printf("Failed to add test result %d\n", i);
            cleanup_json_export(export_data);
            return 0;
        }
    }
    
    // Add all custom data
    for (int i = 0; i < num_custom_data; i++) {
        if (custom_data[i].type && strcmp(custom_data[i].type, "array") == 0) {
            if (!add_custom_int_array(export_data, custom_data[i].key, 
                                     (int*)custom_data[i].value, custom_data[i].size)) {
                printf("Failed to add custom array data %d\n", i);
                cleanup_json_export(export_data);
                return 0;
            }
        } else if (custom_data[i].type && strcmp(custom_data[i].type, "string") == 0) {
            if (!add_custom_string(export_data, custom_data[i].key, 
                                  (char*)custom_data[i].value)) {
                printf("Failed to add custom string data %d\n", i);
                cleanup_json_export(export_data);
                return 0;
            }
        }
    }
    
    // Save to JSON file
    int success = save_chunk_utils_test_results(test_name, export_data);
    
    // Cleanup
    cleanup_json_export(export_data);
    
    return success;
}

t_custom_data create_int_array_data(const char *key, int *array, int size) {
    t_custom_data data;
    data.key = key;
    data.type = "array";
    data.value = array;
    data.size = size;
    return data;
}

t_custom_data create_string_data(const char *key, const char *value) {
    t_custom_data data;
    data.key = key;
    data.type = "string";
    data.value = (void*)value;
    data.size = 0;
    return data;
}

// Helper function to cleanup JSON export structure
void cleanup_json_export(t_json_export *export_data) {
    if (export_data) {
        if (export_data->results) {
            free(export_data->results);
        }
        if (export_data->custom_data) {
            free(export_data->custom_data);
        }
        free(export_data);
    }
}

// Function to save loc_to_stack test results in custom JSON format
void save_loc_to_stack_results(t_ps *data __attribute__((unused)), t_loc_to_stack_test *test_data) {
    cJSON *root = cJSON_CreateArray();
    if (!root) return;
    
    // Test 1: TOP_A
    cJSON *test1 = cJSON_CreateObject();
    cJSON_AddItemToObject(test1, "id", cJSON_CreateNumber(1));
    cJSON_AddItemToObject(test1, "name", cJSON_CreateString("TOP_A"));
    
    cJSON *inputs1 = cJSON_CreateObject();
    cJSON *array1 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test1_top_a.array_size; i++) {
        cJSON_AddItemToArray(array1, cJSON_CreateNumber(test_data->test1_top_a.input_array[i]));
    }
    cJSON_AddItemToObject(inputs1, "array", array1);
    cJSON_AddItemToObject(inputs1, "stack_loc", cJSON_CreateString("TOP_A"));
    cJSON_AddItemToObject(test1, "inputs", inputs1);
    cJSON_AddItemToObject(test1, "result", cJSON_CreateNumber(test_data->test1_top_a.result));
    
    cJSON_AddItemToArray(root, test1);
    
    // Test 2: BOTTOM_A
    cJSON *test2 = cJSON_CreateObject();
    cJSON_AddItemToObject(test2, "id", cJSON_CreateNumber(2));
    cJSON_AddItemToObject(test2, "name", cJSON_CreateString("BOTTOM_A"));
    
    cJSON *inputs2 = cJSON_CreateObject();
    cJSON *array2 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test2_bottom_a.array_size; i++) {
        cJSON_AddItemToArray(array2, cJSON_CreateNumber(test_data->test2_bottom_a.input_array[i]));
    }
    cJSON_AddItemToObject(inputs2, "array", array2);
    cJSON_AddItemToObject(inputs2, "stack_loc", cJSON_CreateString("BOTTOM_A"));
    cJSON_AddItemToObject(test2, "inputs", inputs2);
    cJSON_AddItemToObject(test2, "result", cJSON_CreateNumber(test_data->test2_bottom_a.result));
    
    cJSON_AddItemToArray(root, test2);
    
    // Test 3: TOP_B
    cJSON *test3 = cJSON_CreateObject();
    cJSON_AddItemToObject(test3, "id", cJSON_CreateNumber(3));
    cJSON_AddItemToObject(test3, "name", cJSON_CreateString("TOP_B"));
    
    cJSON *inputs3 = cJSON_CreateObject();
    cJSON *array3 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test3_top_b.array_size; i++) {
        cJSON_AddItemToArray(array3, cJSON_CreateNumber(test_data->test3_top_b.input_array[i]));
    }
    cJSON_AddItemToObject(inputs3, "array", array3);
    cJSON_AddItemToObject(inputs3, "stack_loc", cJSON_CreateString("TOP_B"));
    cJSON_AddItemToObject(test3, "inputs", inputs3);
    cJSON_AddItemToObject(test3, "result", cJSON_CreateNumber(test_data->test3_top_b.result));
    
    cJSON_AddItemToArray(root, test3);
    
    // Test 4: BOTTOM_B
    cJSON *test4 = cJSON_CreateObject();
    cJSON_AddItemToObject(test4, "id", cJSON_CreateNumber(4));
    cJSON_AddItemToObject(test4, "name", cJSON_CreateString("BOTTOM_B"));
    
    cJSON *inputs4 = cJSON_CreateObject();
    cJSON *array4 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test4_bottom_b.array_size; i++) {
        cJSON_AddItemToArray(array4, cJSON_CreateNumber(test_data->test4_bottom_b.input_array[i]));
    }
    cJSON_AddItemToObject(inputs4, "array", array4);
    cJSON_AddItemToObject(inputs4, "stack_loc", cJSON_CreateString("BOTTOM_B"));
    cJSON_AddItemToObject(test4, "inputs", inputs4);
    cJSON_AddItemToObject(test4, "result", cJSON_CreateNumber(test_data->test4_bottom_b.result));
    
    cJSON_AddItemToArray(root, test4);
    
    // Convert to string and save to file
    char *json_string = cJSON_Print(root);
    if (!json_string) {
        cJSON_Delete(root);
        return;
    }
    
    // Create chunk_utils directory if it doesn't exist
    system("mkdir -p data/chunk_utils");
    
    // Save to file
    FILE *file = fopen("data/chunk_utils/loc_to_stack.json", "w");
    if (file) {
        fprintf(file, "%s", json_string);
        fclose(file);
        printf("Results saved to: data/chunk_utils/loc_to_stack.json\n");
    } else {
        printf("Failed to save results to file\n");
    }
    
    // Cleanup
    free(json_string);
    cJSON_Delete(root);
}

// Function to save chunk_value test results in custom JSON format
void save_chunk_value_results(t_ps *data __attribute__((unused)), t_chunk_value_test *test_data) {
    cJSON *root = cJSON_CreateArray();
    if (!root) return;
    
    // Test 1: TOP_A_BASIC
    cJSON *test1 = cJSON_CreateObject();
    cJSON_AddItemToObject(test1, "id", cJSON_CreateNumber(1));
    cJSON_AddItemToObject(test1, "name", cJSON_CreateString("TOP_A_BASIC"));
    
    cJSON *inputs1 = cJSON_CreateObject();
    cJSON *array1 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test1_top_a_basic.array_size; i++) {
        cJSON_AddItemToArray(array1, cJSON_CreateNumber(test_data->test1_top_a_basic.input_array[i]));
    }
    cJSON_AddItemToObject(inputs1, "array", array1);
    cJSON_AddItemToObject(inputs1, "chunk_loc", cJSON_CreateString("TOP_A"));
    cJSON_AddItemToObject(inputs1, "chunk_size", cJSON_CreateNumber(5));
    cJSON_AddItemToObject(inputs1, "offset", cJSON_CreateString("0 (start of chunk)"));
    cJSON_AddItemToObject(test1, "inputs", inputs1);
    cJSON_AddItemToObject(test1, "result", cJSON_CreateNumber(test_data->test1_top_a_basic.result));
    
    cJSON_AddItemToArray(root, test1);
    
    // Test 2: TOP_A_MIDDLE
    cJSON *test2 = cJSON_CreateObject();
    cJSON_AddItemToObject(test2, "id", cJSON_CreateNumber(2));
    cJSON_AddItemToObject(test2, "name", cJSON_CreateString("TOP_A_MIDDLE"));
    
    cJSON *inputs2 = cJSON_CreateObject();
    cJSON *array2 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test2_top_a_middle.array_size; i++) {
        cJSON_AddItemToArray(array2, cJSON_CreateNumber(test_data->test2_top_a_middle.input_array[i]));
    }
    cJSON_AddItemToObject(inputs2, "array", array2);
    cJSON_AddItemToObject(inputs2, "chunk_loc", cJSON_CreateString("TOP_A"));
    cJSON_AddItemToObject(inputs2, "chunk_size", cJSON_CreateNumber(5));
    cJSON_AddItemToObject(inputs2, "offset", cJSON_CreateString("2 (third element in chunk)"));
    cJSON_AddItemToObject(test2, "inputs", inputs2);
    cJSON_AddItemToObject(test2, "result", cJSON_CreateNumber(test_data->test2_top_a_middle.result));
    
    cJSON_AddItemToArray(root, test2);
    
    // Test 3: BOTTOM_B_BASIC
    cJSON *test3 = cJSON_CreateObject();
    cJSON_AddItemToObject(test3, "id", cJSON_CreateNumber(3));
    cJSON_AddItemToObject(test3, "name", cJSON_CreateString("BOTTOM_B_BASIC"));
    
    cJSON *inputs3 = cJSON_CreateObject();
    cJSON *array3 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test3_bottom_b_basic.array_size; i++) {
        cJSON_AddItemToArray(array3, cJSON_CreateNumber(test_data->test3_bottom_b_basic.input_array[i]));
    }
    cJSON_AddItemToObject(inputs3, "array", array3);
    cJSON_AddItemToObject(inputs3, "chunk_loc", cJSON_CreateString("BOTTOM_B"));
    cJSON_AddItemToObject(inputs3, "chunk_size", cJSON_CreateNumber(4));
    cJSON_AddItemToObject(inputs3, "offset", cJSON_CreateString("0 (start of chunk)"));
    cJSON_AddItemToObject(test3, "inputs", inputs3);
    cJSON_AddItemToObject(test3, "result", cJSON_CreateNumber(test_data->test3_bottom_b_basic.result));
    
    cJSON_AddItemToArray(root, test3);
    
    // Test 4: BOTTOM_B_SECOND
    cJSON *test4 = cJSON_CreateObject();
    cJSON_AddItemToObject(test4, "id", cJSON_CreateNumber(4));
    cJSON_AddItemToObject(test4, "name", cJSON_CreateString("BOTTOM_B_SECOND"));
    
    cJSON *inputs4 = cJSON_CreateObject();
    cJSON *array4 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test4_bottom_b_second.array_size; i++) {
        cJSON_AddItemToArray(array4, cJSON_CreateNumber(test_data->test4_bottom_b_second.input_array[i]));
    }
    cJSON_AddItemToObject(inputs4, "array", array4);
    cJSON_AddItemToObject(inputs4, "chunk_loc", cJSON_CreateString("BOTTOM_B"));
    cJSON_AddItemToObject(inputs4, "chunk_size", cJSON_CreateNumber(4));
    cJSON_AddItemToObject(inputs4, "offset", cJSON_CreateString("1 (second element in chunk)"));
    cJSON_AddItemToObject(test4, "inputs", inputs4);
    cJSON_AddItemToObject(test4, "result", cJSON_CreateNumber(test_data->test4_bottom_b_second.result));
    
    cJSON_AddItemToArray(root, test4);
    
    // Test 5: TOP_B_LAST
    cJSON *test5 = cJSON_CreateObject();
    cJSON_AddItemToObject(test5, "id", cJSON_CreateNumber(5));
    cJSON_AddItemToObject(test5, "name", cJSON_CreateString("TOP_B_LAST"));
    
    cJSON *inputs5 = cJSON_CreateObject();
    cJSON *array5 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test5_top_b_last.array_size; i++) {
        cJSON_AddItemToArray(array5, cJSON_CreateNumber(test_data->test5_top_b_last.input_array[i]));
    }
    cJSON_AddItemToObject(inputs5, "array", array5);
    cJSON_AddItemToObject(inputs5, "chunk_loc", cJSON_CreateString("TOP_B"));
    cJSON_AddItemToObject(inputs5, "chunk_size", cJSON_CreateNumber(3));
    cJSON_AddItemToObject(inputs5, "offset", cJSON_CreateString("2 (third element in chunk)"));
    cJSON_AddItemToObject(test5, "inputs", inputs5);
    cJSON_AddItemToObject(test5, "result", cJSON_CreateNumber(test_data->test5_top_b_last.result));
    
    cJSON_AddItemToArray(root, test5);
    
    // Convert to string and save to file
    char *json_string = cJSON_Print(root);
    if (!json_string) {
        cJSON_Delete(root);
        return;
    }
    
    // Create chunk_utils directory if it doesn't exist
    system("mkdir -p data/chunk_utils");
    
    // Save to file
    FILE *file = fopen("data/chunk_utils/chunk_value.json", "w");
    if (file) {
        fprintf(file, "%s", json_string);
        fclose(file);
        printf("Results saved to: data/chunk_utils/chunk_value.json\n");
    } else {
        printf("Failed to save results to file\n");
    }
    
    // Cleanup
    free(json_string);
    cJSON_Delete(root);
}

// Function to save chunk_max_value test results in custom JSON format
void save_chunk_max_value_results(t_ps *data __attribute__((unused)), t_chunk_max_value_test *test_data) {
    cJSON *root = cJSON_CreateArray();
    if (!root) return;
    
    // Test 1: TOP_A, size=5
    cJSON *test1 = cJSON_CreateObject();
    cJSON_AddItemToObject(test1, "id", cJSON_CreateNumber(1));
    cJSON_AddItemToObject(test1, "name", cJSON_CreateString("TOP_A"));
    
    cJSON *inputs1 = cJSON_CreateObject();
    cJSON *array1 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test1_top_a.array_size; i++) {
        cJSON_AddItemToArray(array1, cJSON_CreateNumber(test_data->test1_top_a.input_array[i]));
    }
    cJSON_AddItemToObject(inputs1, "array", array1);
    cJSON_AddItemToObject(inputs1, "chunk_loc", cJSON_CreateString("TOP_A"));
    cJSON_AddItemToObject(inputs1, "chunk_size", cJSON_CreateNumber(5));
    cJSON_AddItemToObject(test1, "inputs", inputs1);
    cJSON_AddItemToObject(test1, "result", cJSON_CreateNumber(test_data->test1_top_a.result));
    
    cJSON_AddItemToArray(root, test1);
    
    // Test 2: BOTTOM_A, size=4
    cJSON *test2 = cJSON_CreateObject();
    cJSON_AddItemToObject(test2, "id", cJSON_CreateNumber(2));
    cJSON_AddItemToObject(test2, "name", cJSON_CreateString("BOTTOM_A"));
    
    cJSON *inputs2 = cJSON_CreateObject();
    cJSON *array2 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test2_bottom_a.array_size; i++) {
        cJSON_AddItemToArray(array2, cJSON_CreateNumber(test_data->test2_bottom_a.input_array[i]));
    }
    cJSON_AddItemToObject(inputs2, "array", array2);
    cJSON_AddItemToObject(inputs2, "chunk_loc", cJSON_CreateString("BOTTOM_A"));
    cJSON_AddItemToObject(inputs2, "chunk_size", cJSON_CreateNumber(4));
    cJSON_AddItemToObject(test2, "inputs", inputs2);
    cJSON_AddItemToObject(test2, "result", cJSON_CreateNumber(test_data->test2_bottom_a.result));
    
    cJSON_AddItemToArray(root, test2);
    
    // Test 3: TOP_B, size=3
    cJSON *test3 = cJSON_CreateObject();
    cJSON_AddItemToObject(test3, "id", cJSON_CreateNumber(3));
    cJSON_AddItemToObject(test3, "name", cJSON_CreateString("TOP_B"));
    
    cJSON *inputs3 = cJSON_CreateObject();
    cJSON *array3 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test3_top_b.array_size; i++) {
        cJSON_AddItemToArray(array3, cJSON_CreateNumber(test_data->test3_top_b.input_array[i]));
    }
    cJSON_AddItemToObject(inputs3, "array", array3);
    cJSON_AddItemToObject(inputs3, "chunk_loc", cJSON_CreateString("TOP_B"));
    cJSON_AddItemToObject(inputs3, "chunk_size", cJSON_CreateNumber(3));
    cJSON_AddItemToObject(test3, "inputs", inputs3);
    cJSON_AddItemToObject(test3, "result", cJSON_CreateNumber(test_data->test3_top_b.result));
    
    cJSON_AddItemToArray(root, test3);
    
    // Test 4: BOTTOM_B, size=4
    cJSON *test4 = cJSON_CreateObject();
    cJSON_AddItemToObject(test4, "id", cJSON_CreateNumber(4));
    cJSON_AddItemToObject(test4, "name", cJSON_CreateString("BOTTOM_B"));
    
    cJSON *inputs4 = cJSON_CreateObject();
    cJSON *array4 = cJSON_CreateArray();
    for (int i = 0; i < test_data->test4_bottom_b.array_size; i++) {
        cJSON_AddItemToArray(array4, cJSON_CreateNumber(test_data->test4_bottom_b.input_array[i]));
    }
    cJSON_AddItemToObject(inputs4, "array", array4);
    cJSON_AddItemToObject(inputs4, "chunk_loc", cJSON_CreateString("BOTTOM_B"));
    cJSON_AddItemToObject(inputs4, "chunk_size", cJSON_CreateNumber(4));
    cJSON_AddItemToObject(test4, "inputs", inputs4);
    cJSON_AddItemToObject(test4, "result", cJSON_CreateNumber(test_data->test4_bottom_b.result));
    
    cJSON_AddItemToArray(root, test4);
    
    // Convert to string and save to file
    char *json_string = cJSON_Print(root);
    if (!json_string) {
        cJSON_Delete(root);
        return;
    }
    
    // Create chunk_utils directory if it doesn't exist
    system("mkdir -p data/chunk_utils");
    
    // Save to file
    FILE *file = fopen("data/chunk_utils/chunk_max_value.json", "w");
    if (file) {
        fprintf(file, "%s", json_string);
        fclose(file);
        printf("Results saved to: data/chunk_utils/chunk_max_value.json\n");
    } else {
        printf("Failed to save results to file\n");
    }
    
    // Cleanup
    free(json_string);
    cJSON_Delete(root);
}
