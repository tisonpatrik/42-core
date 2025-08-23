#include <stdio.h>

// Forward declarations for test functions
int run_loc_to_stack_tests(int size);
int run_chunk_max_value_tests(int size);
int run_chunk_value_tests(int size);

int main(void)
{
    int test_array_size = 10;  // Size for all test arrays
    
    // Run the loc_to_stack test suite
    if (run_loc_to_stack_tests(test_array_size) != 0) {
        printf("Error: Loc to stack tests failed\n");
        return 1;
    }

    // Run the chunk_max_value test suite
    if (run_chunk_max_value_tests(test_array_size) != 0) {
        printf("Error: Chunk max value tests failed\n");
        return 1;
    }

    // Run the chunk_value test suite
    if (run_chunk_value_tests(test_array_size) != 0) {
        printf("Error: Chunk value tests failed\n");
        return 1;
    }

    return (0);
}