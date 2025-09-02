#include "../include/ops.h"
#include "../include/stack.h"
#include <assert.h>
#include <stdio.h>

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

// Test SA (Swap A)
void test_swap_a()
{
    // Arrange
    int numbers[] = {1, 2, 3};
    t_sorting_state *state = create_sorting_state(numbers, 3);
    int expected[] = {2, 1, 3};
    
    // Act
    swap_a(state);
    
    // Assert
    int result = check_stack_content(state->a, expected, 3);
    print_test_result("SA (Swap A)", result);
    
    free_sorting_state(state);
}

// Test SB (Swap B)
void test_swap_b()
{
    // Arrange
    int numbers[] = {4, 5, 6};
    t_sorting_state *state = create_sorting_state(numbers, 3);
    fill_stack(state->b, numbers, 3);
    clear_stack(state->a);
    int expected[] = {5, 4, 6};
    
    // Act
    swap_b(state);
    
    // Assert
    int result = check_stack_content(state->b, expected, 3);
    print_test_result("SB (Swap B)", result);
    
    free_sorting_state(state);
}

// Test SS (Swap both)
void test_swap_ab()
{
    // Arrange
    int numbers_a[] = {1, 2, 3};
    int numbers_b[] = {4, 5, 6};
    t_sorting_state *state = create_sorting_state(numbers_a, 3);
    fill_stack(state->b, numbers_b, 3);
    int expected_a[] = {2, 1, 3};
    int expected_b[] = {5, 4, 6};
    
    // Act
    swap_ab(state);
    
    // Assert
    int result_a = check_stack_content(state->a, expected_a, 3);
    int result_b = check_stack_content(state->b, expected_b, 3);
    int result = result_a && result_b;
    print_test_result("SS (Swap both)", result);
    
    free_sorting_state(state);
}

// Test PA (Push A)
void test_push_a()
{
    // Arrange
    int numbers_a[] = {1, 2};
    int numbers_b[] = {3, 4};
    t_sorting_state *state = create_sorting_state(numbers_a, 2);
    fill_stack(state->b, numbers_b, 2);
    int expected_a[] = {3, 1, 2};
    int expected_b[] = {4};
    
    // Act
    push_a(state);
    
    // Assert
    int result_a = check_stack_content(state->a, expected_a, 3);
    int result_b = check_stack_content(state->b, expected_b, 1);
    int result = result_a && result_b;
    print_test_result("PA (Push A)", result);
    
    free_sorting_state(state);
}

// Test PB (Push B)
void test_push_b()
{
    // Arrange
    int numbers_a[] = {1, 2};
    int numbers_b[] = {3, 4};
    t_sorting_state *state = create_sorting_state(numbers_a, 2);
    fill_stack(state->b, numbers_b, 2);
    int expected_a[] = {2};
    int expected_b[] = {1, 3, 4};
    
    // Act
    push_b(state);
    
    // Assert
    int result_a = check_stack_content(state->a, expected_a, 1);
    int result_b = check_stack_content(state->b, expected_b, 3);
    int result = result_a && result_b;
    print_test_result("PB (Push B)", result);
    
    free_sorting_state(state);
}

// Test RA (Rotate A)
void test_rotate_a()
{
    // Arrange
    int numbers[] = {1, 2, 3, 4};
    t_sorting_state *state = create_sorting_state(numbers, 4);
    int expected[] = {2, 3, 4, 1};
    
    // Act
    rotate_a(state);
    
    // Assert
    int result = check_stack_content(state->a, expected, 4);
    print_test_result("RA (Rotate A)", result);
    
    free_sorting_state(state);
}

// Test RB (Rotate B)
void test_rotate_b()
{
    // Arrange
    int numbers[] = {4, 5, 6, 7};
    t_sorting_state *state = create_sorting_state(numbers, 4);
    fill_stack(state->b, numbers, 4);
    clear_stack(state->a);
    int expected[] = {5, 6, 7, 4};
    
    // Act
    rotate_b(state);
    
    // Assert
    int result = check_stack_content(state->b, expected, 4);
    print_test_result("RB (Rotate B)", result);
    
    free_sorting_state(state);
}

// Test RR (Rotate both)
void test_rotate_ab()
{
    // Arrange
    int numbers_a[] = {1, 2, 3};
    int numbers_b[] = {4, 5, 6};
    t_sorting_state *state = create_sorting_state(numbers_a, 3);
    fill_stack(state->b, numbers_b, 3);
    int expected_a[] = {2, 3, 1};
    int expected_b[] = {5, 6, 4};
    
    // Act
    rotate_ab(state);
    
    // Assert
    int result_a = check_stack_content(state->a, expected_a, 3);
    int result_b = check_stack_content(state->b, expected_b, 3);
    int result = result_a && result_b;
    print_test_result("RR (Rotate both)", result);
    
    free_sorting_state(state);
}

// Test RRA (Reverse rotate A)
void test_reverse_rotate_a()
{
    // Arrange
    int numbers[] = {1, 2, 3, 4};
    t_sorting_state *state = create_sorting_state(numbers, 4);
    int expected[] = {4, 1, 2, 3};
    
    // Act
    reverse_rotate_a(state);
    
    // Assert
    int result = check_stack_content(state->a, expected, 4);
    print_test_result("RRA (Reverse rotate A)", result);
    
    free_sorting_state(state);
}

// Test RRB (Reverse rotate B)
void test_reverse_rotate_b()
{
    // Arrange
    int numbers[] = {4, 5, 6, 7};
    t_sorting_state *state = create_sorting_state(numbers, 4);
    fill_stack(state->b, numbers, 4);
    clear_stack(state->a);
    int expected[] = {7, 4, 5, 6};
    
    // Act
    reverse_rotate_b(state);
    
    // Assert
    int result = check_stack_content(state->b, expected, 4);
    print_test_result("RRB (Reverse rotate B)", result);
    
    free_sorting_state(state);
}

// Test RRR (Reverse rotate both)
void test_reverse_rotate_ab()
{
    // Arrange
    int numbers_a[] = {1, 2, 3};
    int numbers_b[] = {4, 5, 6};
    t_sorting_state *state = create_sorting_state(numbers_a, 3);
    fill_stack(state->b, numbers_b, 3);
    int expected_a[] = {3, 1, 2};
    int expected_b[] = {6, 4, 5};
    
    // Act
    reverse_rotate_ab(state);
    
    // Assert
    int result_a = check_stack_content(state->a, expected_a, 3);
    int result_b = check_stack_content(state->b, expected_b, 3);
    int result = result_a && result_b;
    print_test_result("RRR (Reverse rotate both)", result);
    
    free_sorting_state(state);
}

int main()
{
    printf("🧪 Running Push Swap Operation Tests\n");
    printf("=====================================\n\n");
    
    test_swap_a();
    test_swap_b();
    test_swap_ab();
    test_push_a();
    test_push_b();
    test_rotate_a();
    test_rotate_b();
    test_rotate_ab();
    test_reverse_rotate_a();
    test_reverse_rotate_b();
    test_reverse_rotate_ab();
    
    printf("\n✨ All tests completed!\n");
    return 0;
}
