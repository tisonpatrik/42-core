#include <stdio.h>
#include "../include/chunk_utils_task.h"

// Function declaration for run_chunk_utils_tasks
int run_chunk_utils_tasks(void);

int main(void)
{
    // Run the chunk utils test suite
    if (run_chunk_utils_tasks() != 0) {
        printf("Error: Chunk utils tests failed\n");
        return 1;
    }

    return (0);
}