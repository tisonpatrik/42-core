#include "../include/separator.h"
#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "test_main.h"

// Debug function to print LIS nodes
void test_lis_debug_function(void)
{

    //Arrange
    int values[] = {3, 5, 2, 6, 1, 4, 0, 7, 9, 8, 10};
    int expected_a[] = {3, 5, 6, 7, 9, 10};
    int expected_b[] = {8, 4, 1, 2, 0};
    
    t_sorting_state *state = create_sorting_state(values, 11);

    //Act
    push_non_lis_into_b(state);
    
    //Assert
    assert(check_stack_content(state->a, expected_a, 6));
    assert(check_stack_content(state->b, expected_b, 5));

    //Cleanup
    free_sorting_state(state);
}