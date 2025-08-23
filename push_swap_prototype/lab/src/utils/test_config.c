#include "../../include/testing/test_config.h"
#include <stdlib.h>
#include <string.h>

// Default configuration values - centralized in one place
const t_test_config DEFAULT_TEST_CONFIG = {
    .test_array_size = 10,
    .output_directory = "data/chunk_utils",
    .verbose_output = 0,
    .random_seed = 42,  // Fixed seed for reproducible tests
    
    .chunk_sizes = {
        .top_a_size = 5,
        .bottom_a_size = 4,
        .top_b_size = 3,
        .bottom_b_size = 4
    },
    
    .test_counts = {
        .loc_to_stack_count = 4,
        .chunk_max_value_count = 4,
        .chunk_value_count = 5
    }
};

// Create a new test configuration
t_test_config* create_test_config(int array_size, const char *output_dir, int verbose) {
    t_test_config *config = malloc(sizeof(t_test_config));
    if (!config) return NULL;
    
    // Copy default values
    *config = DEFAULT_TEST_CONFIG;
    
    // Override with provided values
    if (array_size > 0) {
        config->test_array_size = array_size;
    }
    
    if (output_dir) {
        config->output_directory = strdup(output_dir);
    }
    
    config->verbose_output = verbose;
    
    return config;
}

// Free test configuration
void free_test_config(t_test_config *config) {
    if (!config) return;
    
    // Free dynamically allocated strings
    if (config->output_directory && 
        config->output_directory != DEFAULT_TEST_CONFIG.output_directory) {
        free((void*)config->output_directory);
    }
    
    free(config);
}

// Get default test configuration
t_test_config* get_default_test_config(void) {
    return create_test_config(10, "data/chunk_utils", 0);
}

// Validate test configuration
int validate_test_config(const t_test_config *config) {
    if (!config) return 0;
    
    // Validate array size
    if (config->test_array_size <= 0) return 0;
    
    // Validate chunk sizes
    if (config->chunk_sizes.top_a_size <= 0 ||
        config->chunk_sizes.bottom_a_size <= 0 ||
        config->chunk_sizes.top_b_size <= 0 ||
        config->chunk_sizes.bottom_b_size <= 0) {
        return 0;
    }
    
    // Validate test counts
    if (config->test_counts.loc_to_stack_count <= 0 ||
        config->test_counts.chunk_max_value_count <= 0 ||
        config->test_counts.chunk_value_count <= 0) {
        return 0;
    }
    
    return 1;
}
