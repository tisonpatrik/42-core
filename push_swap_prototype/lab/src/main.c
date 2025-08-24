#include "../include/testing/chunk_utils_tests.h"
#include "../include/testing/chunk_split_tests.h"

// Forward declarations
extern int run_loc_to_stack_tests(int size);
extern int run_chunk_max_value_tests(int size);
extern int run_chunk_value_tests(int size);
extern int run_chunk_split_tests(int size);

int main(void)
{    
    int result = 0;
    int size = 100;
    
    // Run chunk utils tests
    result += run_loc_to_stack_tests(size);
    result += run_chunk_max_value_tests(size);
    result += run_chunk_value_tests(size);
    
    // Run chunk split tests
    result += run_chunk_split_tests(size);
        
    return result;
}