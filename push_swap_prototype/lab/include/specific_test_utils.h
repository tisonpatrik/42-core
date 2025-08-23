#ifndef SPECIFIC_TEST_UTILS_H
# define SPECIFIC_TEST_UTILS_H

// Forward declarations
struct s_chunk_max_value_test;
typedef struct s_chunk_max_value_test t_chunk_max_value_test;
struct s_chunk_value_test;
typedef struct s_chunk_value_test t_chunk_value_test;
struct s_loc_to_stack_test;
typedef struct s_loc_to_stack_test t_loc_to_stack_test;

// Chunk max value test utilities
t_chunk_max_value_test* create_chunk_max_value_test(int id, const char *name, int *input_array, int array_size, int result, const char *chunk_loc, int chunk_size);
void free_chunk_max_value_test(t_chunk_max_value_test *test);

// Chunk value test utilities
t_chunk_value_test* create_chunk_value_test(int id, const char *name, int *input_array, int array_size, int result, const char *chunk_loc, int chunk_size, int offset);
void free_chunk_value_test(t_chunk_value_test *test);

// Loc to stack test utilities
t_loc_to_stack_test* create_loc_to_stack_test(int id, const char *name, int *input_array, int array_size, int result, const char *stack_loc);
void free_loc_to_stack_test(t_loc_to_stack_test *test);

#endif
