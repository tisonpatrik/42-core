#include "../include/testing/chunk_utils_tests.h"
#include <stdio.h>

// Forward declarations
extern int run_loc_to_stack_tests(int size);
extern int run_chunk_max_value_tests(int size);
extern int run_chunk_value_tests(int size);

int main(void)
{
    printf("🚀 Running tests with size: 10\n");
    
    int result = 0;
    int size = 100;
    result += run_loc_to_stack_tests(size);
    result += run_chunk_max_value_tests(size);
    result += run_chunk_value_tests(size);
    
    printf("🎯 Tests completed! %s\n", result == 0 ? "All passed!" : "Some failed!");
    
    return result;
}