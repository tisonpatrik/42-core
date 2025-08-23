#include "../../include/json_utils.h"
#include "../../include/chunk_utils_task.h"
#include "../../include/chunk_utils_common.h"
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



// Helper function to create test case from chunk max value data
static t_test_case create_chunk_max_value_test_case(int id, const char *name, 
                                                   int *chunk_data, int chunk_size,
                                                   const char *chunk_loc, int chunk_size_param,
                                                   int result) {
    t_test_case test_case = {0};
    test_case.id = id;
    test_case.name = (char*)name;
    test_case.input_array = chunk_data;
    test_case.array_size = chunk_size;
    test_case.result = result;
    test_case.param1_name = (char*)"chunk_loc";
    test_case.param1_value = (char*)chunk_loc;
    test_case.param2_name = (char*)"chunk_size";
    test_case.param2_value = chunk_size_param;
    return test_case;
}

// Helper function to create test case from loc to stack data
static t_test_case create_loc_to_stack_test_case(int id, const char *name,
                                                int *stack_data, int stack_size,
                                                const char *stack_loc, int result) {
    t_test_case test_case = {0};
    test_case.id = id;
    test_case.name = (char*)name;
    test_case.input_array = stack_data;
    test_case.array_size = stack_size;
    test_case.result = result;
    test_case.param1_name = (char*)"stack_loc";
    test_case.param1_value = (char*)stack_loc;
    return test_case;
}

// Helper function to create test case from chunk value data
static t_test_case create_chunk_value_test_case(int id, const char *name,
                                               int *input_array, int array_size,
                                               const char *chunk_loc, int chunk_size,
                                               const char *offset_desc, int result) {
    t_test_case test_case = {0};
    test_case.id = id;
    test_case.name = (char*)name;
    test_case.input_array = input_array;
    test_case.array_size = array_size;
    test_case.result = result;
    test_case.param1_name = (char*)"chunk_loc";
    test_case.param1_value = (char*)chunk_loc;
    test_case.param2_name = (char*)"chunk_size";
    test_case.param2_value = chunk_size;
    test_case.param3_name = (char*)"offset";
    test_case.param3_value = (char*)offset_desc;
    return test_case;
}

// Helper function to save test batch to JSON file
static int save_test_batch_to_file(const char *filename, t_test_batch *batch) {
    if (!batch || !filename) return 0;
    
    cJSON *root = cJSON_CreateArray();
    if (!root) return 0;
    
    for (int i = 0; i < batch->num_tests; i++) {
        t_test_case *test = &batch->tests[i];
        cJSON *test_obj = cJSON_CreateObject();
        if (!test_obj) continue;
        
        cJSON_AddItemToObject(test_obj, "id", cJSON_CreateNumber(test->id));
        cJSON_AddItemToObject(test_obj, "name", cJSON_CreateString(test->name));
        
        // Create inputs object
        cJSON *inputs = cJSON_CreateObject();
        if (inputs) {
            // Add array
            cJSON *array = cJSON_CreateArray();
            if (array && test->input_array) {
                for (int j = 0; j < test->array_size; j++) {
                    cJSON_AddItemToArray(array, cJSON_CreateNumber(test->input_array[j]));
                }
                cJSON_AddItemToObject(inputs, "array", array);
            }
            
            // Add parameters
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
        }
        
        cJSON_AddItemToObject(test_obj, "result", cJSON_CreateNumber(test->result));
        cJSON_AddItemToArray(root, test_obj);
    }
    
    // Convert to string and save
    char *json_string = cJSON_Print(root);
    if (!json_string) {
        cJSON_Delete(root);
        return 0;
    }
    
    // Create directory and save file
    system("mkdir -p data/chunk_utils");
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
    
    free(json_string);
    cJSON_Delete(root);
    return success;
}

// Refactored function to save chunk_max_value test results
void save_chunk_max_value_results(t_ps *data __attribute__((unused)), t_chunk_max_value_test *test_data) {
    if (!test_data) return;
    
    // Create test batch
    t_test_batch *batch = create_test_batch("chunk_max_value", 4);
    if (!batch) return;
    
    // Create test cases
    t_test_case test1 = create_chunk_max_value_test_case(1, "TOP_A", 
                                                        test_data->chunk_data, test_data->chunk_size,
                                                        "TOP_A", 5, test_data->max_value_a);
    t_test_case test2 = create_chunk_max_value_test_case(2, "BOTTOM_A", 
                                                        test_data->chunk_data, test_data->chunk_size,
                                                        "BOTTOM_A", 4, test_data->max_value_b);
    t_test_case test3 = create_chunk_max_value_test_case(3, "TOP_B", 
                                                        test_data->chunk_data, test_data->chunk_size,
                                                        "TOP_B", 3, test_data->max_value_combined);
    t_test_case test4 = create_chunk_max_value_test_case(4, "BOTTOM_B", 
                                                        test_data->chunk_data, test_data->chunk_size,
                                                        "BOTTOM_B", 4, test_data->max_value_combined);
    
    // Add tests to batch
    add_test_to_batch(batch, 0, &test1);
    add_test_to_batch(batch, 1, &test2);
    add_test_to_batch(batch, 2, &test3);
    add_test_to_batch(batch, 3, &test4);
    
    // Save to file
    save_test_batch_to_file("data/chunk_utils/chunk_max_value.json", batch);
    
    // Cleanup
    free_test_batch(batch);
}

// Refactored function to save loc_to_stack test results
void save_loc_to_stack_results(t_ps *data __attribute__((unused)), t_loc_to_stack_test *test_data) {
    if (!test_data) return;
    
    // Create test batch
    t_test_batch *batch = create_test_batch("loc_to_stack", 4);
    if (!batch) return;
    
    // Create test cases
    t_test_case test1 = create_loc_to_stack_test_case(1, "TOP_A", 
                                                     test_data->stack_a_data, test_data->stack_a_size,
                                                     "TOP_A", test_data->top_a_result);
    t_test_case test2 = create_loc_to_stack_test_case(2, "BOTTOM_A", 
                                                     test_data->stack_a_data, test_data->stack_a_size,
                                                     "BOTTOM_A", test_data->bottom_a_result);
    t_test_case test3 = create_loc_to_stack_test_case(3, "TOP_B", 
                                                     test_data->stack_b_data, test_data->stack_b_size,
                                                     "TOP_B", test_data->top_b_result);
    t_test_case test4 = create_loc_to_stack_test_case(4, "BOTTOM_B", 
                                                     test_data->stack_b_data, test_data->stack_b_size,
                                                     "BOTTOM_B", test_data->bottom_b_result);
    
    // Add tests to batch
    add_test_to_batch(batch, 0, &test1);
    add_test_to_batch(batch, 1, &test2);
    add_test_to_batch(batch, 2, &test3);
    add_test_to_batch(batch, 3, &test4);
    
    // Save to file
    save_test_batch_to_file("data/chunk_utils/loc_to_stack.json", batch);
    
    // Cleanup
    free_test_batch(batch);
}

// Refactored function to save chunk_value test results
void save_chunk_value_results(t_ps *data __attribute__((unused)), t_chunk_value_test *test_data) {
    if (!test_data) return;
    
    // Create test batch
    t_test_batch *batch = create_test_batch("chunk_value", 5);
    if (!batch) return;
    
    // Create test cases
    t_test_case test1 = create_chunk_value_test_case(1, "TOP_A_BASIC", 
                                                    test_data->test1_top_a_basic.input_array,
                                                    test_data->test1_top_a_basic.array_size,
                                                    "TOP_A", 5, "0 (start of chunk)",
                                                    test_data->test1_top_a_basic.result);
    t_test_case test2 = create_chunk_value_test_case(2, "TOP_A_MIDDLE", 
                                                    test_data->test2_top_a_middle.input_array,
                                                    test_data->test2_top_a_middle.array_size,
                                                    "TOP_A", 5, "2 (third element in chunk)",
                                                    test_data->test2_top_a_middle.result);
    t_test_case test3 = create_chunk_value_test_case(3, "BOTTOM_B_BASIC", 
                                                    test_data->test3_bottom_b_basic.input_array,
                                                    test_data->test3_bottom_b_basic.array_size,
                                                    "BOTTOM_B", 4, "0 (start of chunk)",
                                                    test_data->test3_bottom_b_basic.result);
    t_test_case test4 = create_chunk_value_test_case(4, "BOTTOM_B_SECOND", 
                                                    test_data->test4_bottom_b_second.input_array,
                                                    test_data->test4_bottom_b_second.array_size,
                                                    "BOTTOM_B", 4, "1 (second element in chunk)",
                                                    test_data->test4_bottom_b_second.result);
    t_test_case test5 = create_chunk_value_test_case(5, "TOP_B_LAST", 
                                                    test_data->test5_top_b_last.input_array,
                                                    test_data->test5_top_b_last.array_size,
                                                    "TOP_B", 3, "2 (third element in chunk)",
                                                    test_data->test5_top_b_last.result);
    
    // Add tests to batch
    add_test_to_batch(batch, 0, &test1);
    add_test_to_batch(batch, 1, &test2);
    add_test_to_batch(batch, 2, &test3);
    add_test_to_batch(batch, 3, &test4);
    add_test_to_batch(batch, 4, &test5);
    
    // Save to file
    save_test_batch_to_file("data/chunk_utils/chunk_value.json", batch);
    
    // Cleanup
    free_test_batch(batch);
}
