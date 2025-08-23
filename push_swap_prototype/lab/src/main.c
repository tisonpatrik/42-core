#include <stdio.h>
#include "../include/testing/test_runner.h"

int main(void)
{
    // Create test configuration (can be extended with command line args later)
    t_test_config *config = get_default_test_config();
    if (!config) {
        printf("Error: Failed to create test configuration\n");
        return 1;
    }
    
    // Run all test suites through the test runner
    int result = run_all_test_suites(config);
    
    // Cleanup
    free_test_config(config);
    
    return result;
}