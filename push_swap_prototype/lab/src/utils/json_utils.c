#include "../../include/json_utils.h"
#include "../../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Core JSON utility functions
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

// Data manipulation utilities
t_test_result create_test_result(int id, const char *name, int value) {
    t_test_result result;
    result.id = id;
    result.name = name;
    result.value = value;
    return result;
}

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

// File I/O utilities
int ensure_directory_exists(const char *path) {
    if (!path) return 0;
    
    char mkdir_cmd[512];
    snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p %s", path);
    return system(mkdir_cmd) == 0;
}

int save_json_to_file(const char *filepath, const char *json_string) {
    if (!filepath || !json_string) return 0;
    
    FILE *file = fopen(filepath, "w");
    if (!file) return 0;
    
    int success = fprintf(file, "%s", json_string) > 0;
    fclose(file);
    
    if (success) {
        printf("Results saved to: %s\n", filepath);
    } else {
        printf("Failed to save results to file: %s\n", filepath);
    }
    
    return success;
}

// JSON serialization utilities
char *serialize_json_export(t_json_export *export_data) {
    if (!export_data) return NULL;
    
    cJSON *root = cJSON_CreateObject();
    if (!root) return NULL;
    
    // Add metadata
    cJSON_AddItemToObject(root, "title", cJSON_CreateString(export_data->title));
    cJSON_AddItemToObject(root, "description", cJSON_CreateString(export_data->description));
    
    // Add test results
    cJSON *tests = cJSON_CreateArray();
    if (!tests) {
        cJSON_Delete(root);
        return NULL;
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
    
    // Convert to string
    char *json_string = cJSON_Print(root);
    cJSON_Delete(root);
    
    return json_string;
}

int save_test_results_to_json(const char *filepath, t_json_export *export_data) {
    if (!export_data || !filepath) return 0;
    
    // Serialize to JSON string
    char *json_string = serialize_json_export(export_data);
    if (!json_string) return 0;
    
    // Ensure directory exists
    char dir_path[256];
    snprintf(dir_path, sizeof(dir_path), "%s", filepath);
    char *last_slash = strrchr(dir_path, '/');
    if (last_slash) {
        *last_slash = '\0';
        ensure_directory_exists(dir_path);
    }
    
    // Save to file
    int success = save_json_to_file(filepath, json_string);
    
    // Cleanup
    free(json_string);
    
    return success;
}
