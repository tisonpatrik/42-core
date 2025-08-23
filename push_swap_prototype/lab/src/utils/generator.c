#include <stdlib.h>
#include <time.h>

int * generate_random_array(int size)
{
    int *array = malloc(size * sizeof(int));
    
    // Seed the random number generator
    srand(time(NULL));
    
    // Initialize array with numbers 0 to size-1
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }
    
    // Fisher-Yates shuffle to randomize the order
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        // Swap elements
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    
    return array;
}