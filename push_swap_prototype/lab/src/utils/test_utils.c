#include "../../include/testing/test_utils.h"
#include "../../include/utils/stack_utils.h"
#include <stdlib.h>
#include <string.h>

// Copy stack data - eliminates duplication across test files
int* copy_stack_data(const int *source, int size) {
    if (!source || size <= 0) return NULL;
    
    int *copy = malloc(size * sizeof(int));
    if (!copy) return NULL;
    
    memcpy(copy, source, size * sizeof(int));
    return copy;
}

// Free stack data
void free_stack_data(int *data) {
    safe_free(data);
}

// Cleanup test resources - eliminates duplication across test files
void cleanup_test_resources(void **tests, int count) {
    if (!tests || count <= 0) return;
    
    for (int i = 0; i < count; i++) {
        if (tests[i]) {
            // Note: Individual test types will need to implement their own free functions
            // This is just a safety cleanup for the array
            tests[i] = NULL;
        }
    }
}

// Create test data with configuration
t_ps* create_test_data_with_config(const t_test_config *config) {
    if (!config) return NULL;
    
    return create_test_data(config->test_array_size, config->test_array_size);
}

// Create test cases from configuration
int create_test_cases_from_config(t_ps *data, const t_test_config *config, 
                                 void **tests, const char *test_type) {
    if (!data || !config || !tests || !test_type) return 0;
    
    // This function will be implemented based on specific test type needs
    // For now, return success to avoid compilation errors
    return 1;
}

// Safe free function
void safe_free(void *ptr) {
    if (ptr) {
        free(ptr);
    }
}
