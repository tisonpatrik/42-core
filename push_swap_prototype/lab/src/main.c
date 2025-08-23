#include <stdio.h>
#include "../include/chunk_utils_task.h"

// Function declarations
int run_loc_to_stack_tests(void);
int run_chunk_max_value_tests(void);
int run_chunk_value_tests(void);

int main(void)
{
    // Run the loc_to_stack test suite
    if (run_loc_to_stack_tests() != 0) {
        printf("Error: Loc to stack tests failed\n");
        return 1;
    }

    // Run the chunk_max_value test suite
    if (run_chunk_max_value_tests() != 0) {
        printf("Error: Chunk max value tests failed\n");
        return 1;
    }

    // Run the chunk_value test suite
    if (run_chunk_value_tests() != 0) {
        printf("Error: Chunk value tests failed\n");
        return 1;
    }

    return (0);
}