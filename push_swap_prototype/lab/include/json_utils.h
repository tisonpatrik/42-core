#ifndef JSON_UTILS_H
# define JSON_UTILS_H

#include <time.h>

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

// Core JSON utility functions
t_json_export *create_json_export(const char *title, const char *description);
void cleanup_json_export(t_json_export *export_data);

// Data manipulation utilities
t_test_result create_test_result(int id, const char *name, int value);
int add_test_result(t_json_export *export_data, t_test_result result);
int add_custom_int_array(t_json_export *export_data, const char *key, int *array, int size);
int add_custom_string(t_json_export *export_data, const char *key, const char *value);
t_custom_data create_int_array_data(const char *key, int *array, int size);
t_custom_data create_string_data(const char *key, const char *value);

// File I/O utilities moved to file_utils.h

// JSON serialization utilities
char *serialize_json_export(t_json_export *export_data);
int save_test_results_to_json(const char *filepath, t_json_export *export_data);

// Forward declaration for test batch types
struct s_test_batch;
typedef struct s_test_batch t_test_batch;

// Test batch JSON export functionality
void save_test_batch_to_json(t_test_batch *batch, const char *filename);

#endif
