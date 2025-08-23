#ifndef SPECIFIC_JSON_UTILS_H
# define SPECIFIC_JSON_UTILS_H

// Forward declarations
struct s_chunk_max_value_test;
typedef struct s_chunk_max_value_test t_chunk_max_value_test;
struct s_chunk_value_test;
typedef struct s_chunk_value_test t_chunk_value_test;
struct s_loc_to_stack_test;
typedef struct s_loc_to_stack_test t_loc_to_stack_test;

// JSON export functions for specific test structures
void save_chunk_max_value_tests_to_json(t_chunk_max_value_test **tests, int num_tests, const char *filename);
void save_chunk_value_tests_to_json(t_chunk_value_test **tests, int num_tests, const char *filename);
void save_loc_to_stack_tests_to_json(t_loc_to_stack_test **tests, int num_tests, const char *filename);

#endif
