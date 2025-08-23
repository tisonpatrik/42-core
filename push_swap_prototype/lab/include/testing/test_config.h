#ifndef TEST_CONFIG_H
# define TEST_CONFIG_H

#include "../core/types.h"

// Test configuration structure
typedef struct s_test_config {
    int test_array_size;
    const char *output_directory;
    int verbose_output;
    unsigned int random_seed;        // For reproducible tests
    
    // Chunk size configuration
    struct {
        int top_a_size;
        int bottom_a_size;
        int top_b_size;
        int bottom_b_size;
    } chunk_sizes;
    
    // Test counts for different test types
    struct {
        int loc_to_stack_count;
        int chunk_max_value_count;
        int chunk_value_count;
    } test_counts;
} t_test_config;

// Default configuration values
extern const t_test_config DEFAULT_TEST_CONFIG;

// Configuration management functions
t_test_config* create_test_config(int array_size, const char *output_dir, int verbose);
void free_test_config(t_test_config *config);
t_test_config* get_default_test_config(void);

// Configuration validation
int validate_test_config(const t_test_config *config);

#endif
