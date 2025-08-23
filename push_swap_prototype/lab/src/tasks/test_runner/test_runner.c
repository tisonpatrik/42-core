#include "../../../include/testing/test_runner.h"
#include "../../../include/testing/chunk_utils_tests.h"
#include "../../../include/testing/test_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test suite definitions
static const t_test_suite test_suites[] = {
    {"loc_to_stack", run_loc_to_stack_tests},
    {"chunk_max_value", run_chunk_max_value_tests},
    {"chunk_value", run_chunk_value_tests}
};

static const int NUM_TEST_SUITES = sizeof(test_suites) / sizeof(test_suites[0]);

// Run a single test suite
int run_test_suite(const t_test_suite *suite, const t_test_config *config, t_test_result *result) {
    if (!suite || !config || !result) return 0;
    
    result->test_name = suite->name;
    result->error_message = NULL;
    
    if (config->verbose_output) {
        printf("Running test suite: %s\n", suite->name);
    }
    
    int test_result = suite->run_test(config->test_array_size);
    
    if (test_result == 0) {
        result->success = 1;
        if (config->verbose_output) {
            printf("✅ %s tests passed\n", suite->name);
        }
    } else {
        result->success = 0;
        result->error_message = "Test execution failed";
        if (config->verbose_output) {
            printf("❌ %s tests failed\n", suite->name);
        }
    }
    
    return result->success;
}

// Run all test suites
int run_all_test_suites(const t_test_config *config) {
    if (!config) return 0;
    
    printf("🚀 Starting test execution with array size: %d\n", config->test_array_size);
    
    int all_passed = 1;
    t_test_result results[NUM_TEST_SUITES];
    
    // Run each test suite
    for (int i = 0; i < NUM_TEST_SUITES; i++) {
        if (!run_test_suite(&test_suites[i], config, &results[i])) {
            all_passed = 0;
        }
    }
    
    // Print summary
    printf("\n📊 Test Results Summary:\n");
    for (int i = 0; i < NUM_TEST_SUITES; i++) {
        printf("  %s: %s\n", 
               results[i].test_name,
               results[i].success ? "✅ PASSED" : "❌ FAILED");
    }
    
    if (all_passed) {
        printf("\n🎉 All test suites passed successfully!\n");
    } else {
        printf("\n⚠️  Some test suites failed. Check output above for details.\n");
    }
    
    return all_passed ? 0 : 1;
}
