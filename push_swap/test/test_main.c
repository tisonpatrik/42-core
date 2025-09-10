#include "../include/stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "test_main.h"

// Test helper function to print test result
void print_test_result(const char *test_name, int passed)
{
    if (passed)
        printf("✅ %s: PASSED\n", test_name);
    else
        printf("❌ %s: FAILED\n", test_name);
}

// Test helper function to check if stack has expected content
int check_stack_content(t_stack *stack, int *expected, int expected_size)
{
    if (get_size(stack) != expected_size)
        return 0;
    
    t_node *current = get_head(stack);
    for (int i = 0; i < expected_size; i++)
    {
        if (!current || get_content(current) != expected[i])
            return 0;
        current = get_next(current);
    }
    return 1;
}


int main()
{
    printf("🧪 Running Push Swap Tests\n");
    printf("=====================================\n\n");
    
    test_swap_operations();
    test_push_operations();
    test_rotate_operations();
    test_reverse_rotate_operations();
    test_is_sorted_function();
    test_lis_operations();
    test_pick_near_best_operations();
    
    printf("\n✨ All tests completed!\n");
    return 0;
}
