#include "../../include/json_utils.h"
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
