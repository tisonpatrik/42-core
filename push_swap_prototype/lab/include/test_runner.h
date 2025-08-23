#ifndef TEST_RUNNER_H
# define TEST_RUNNER_H

// Test configuration structure
typedef struct s_test_config {
    int test_array_size;
    const char *output_directory;
    int verbose_output;
} t_test_config;

// Test result structure
typedef struct s_test_result {
    const char *test_name;
    int success;
    const char *error_message;
} t_test_result;

// Test suite structure
typedef struct s_test_suite {
    const char *name;
    int (*run_test)(int size);
} t_test_suite;

// Test runner functions
t_test_config* create_test_config(int array_size, const char *output_dir, int verbose);
void free_test_config(t_test_config *config);

int run_test_suite(const t_test_suite *suite, const t_test_config *config, t_test_result *result);
int run_all_test_suites(const t_test_config *config);

// Default test configuration
t_test_config* get_default_test_config(void);

#endif
