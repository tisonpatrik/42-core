#ifndef TEST_UTILS_H
# define TEST_UTILS_H

// Forward declarations
struct s_push_swap;
typedef struct s_push_swap t_ps;
struct s_test_case;
typedef struct s_test_case t_test_case;
struct s_test_batch;
typedef struct s_test_batch t_test_batch;

// Test data management utilities
t_ps* create_test_data(int stack_a_size, int stack_b_size);
void cleanup_test_data(t_ps *data);

// Test case management utilities
t_test_case* create_test_case(int id, const char *name, int *input_array, int array_size, int result);
void set_test_param1(t_test_case *test, const char *name, const char *value);
void set_test_param2(t_test_case *test, const char *name, int value);
void set_test_param3(t_test_case *test, const char *name, const char *value);
void free_test_case(t_test_case *test);

// Test batch management utilities
t_test_batch* create_test_batch(const char *test_type, int num_tests);
void add_test_to_batch(t_test_batch *batch, int index, t_test_case *test);
void free_test_batch(t_test_batch *batch);

#endif
