#include <stdlib.h>
#include <time.h>

static int seed_initialized = 0;

// Generate random array without duplicates for proper testing
int* generate_test_array(int size) {
    int *array = malloc(size * sizeof(int));
    if (!array) return NULL;
    
    // Initialize seed only once
    if (!seed_initialized) {
        srand(time(NULL));
        seed_initialized = 1;
    }
    
    // Initialize with sequential numbers 0 to size-1
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }
    
    // Fisher-Yates shuffle to randomize without duplicates
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap elements
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    
    return array;
}