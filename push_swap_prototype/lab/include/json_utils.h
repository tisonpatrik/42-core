#ifndef JSON_UTILS_H
# define JSON_UTILS_H

#include <time.h>
#include "chunk_utils_task.h"

// Generic structure for test results
typedef struct s_test_result {
    int id;
    const char *name;
    int value;
} t_test_result;

// Generic structure for custom data
typedef struct s_custom_data {
    const char *key;
    const char *type;  // "array", "object", "string", "number"
    void *value;
    int size;  // For arrays
} t_custom_data;

// Generic structure for JSON export data
typedef struct s_json_export {
    const char *title;
    const char *description;
    time_t timestamp;
    int num_results;
    t_test_result *results;
    int num_custom_data;
    t_custom_data *custom_data;
} t_json_export;

// Generic function to save test results to JSON
int save_test_results_to_json(const char *filename_prefix, t_json_export *export_data);

// Special function for chunk_utils tests - saves to chunk_utils directory with specific test name
int save_chunk_utils_test_results(const char *test_name, t_json_export *export_data);

// Generic function to save test results with custom data
int save_generic_test_results(const char *test_name, 
                             const char *title, 
                             const char *description,
                             t_test_result *results, 
                             int num_results,
                             t_custom_data *custom_data, 
                             int num_custom_data);

// Helper function to create test result
t_test_result create_test_result(int id, const char *name, int value);

// Helper function to create JSON export structure
t_json_export *create_json_export(const char *title, const char *description);

// Helper function to add test result to export
int add_test_result(t_json_export *export_data, t_test_result result);

// Helper function to add custom data (array of integers)
int add_custom_int_array(t_json_export *export_data, const char *key, int *array, int size);

// Helper function to add custom data (string)
int add_custom_string(t_json_export *export_data, const char *key, const char *value);

// Helper function to create custom data for integer arrays
t_custom_data create_int_array_data(const char *key, int *array, int size);

// Helper function to create custom data for strings
t_custom_data create_string_data(const char *key, const char *value);

// Helper function to cleanup JSON export structure
void cleanup_json_export(t_json_export *export_data);



#endif
