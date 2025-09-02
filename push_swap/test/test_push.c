#include "test_main.h"

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
    int numbers_a[] = {1, 2, 3};
    int numbers_b[] = {4};
    t_sorting_state *state = create_sorting_state(numbers_a, 3);
    fill_stack(state->b, numbers_b, 1);
    int expected_a[] = {2, 3};
    int expected_b[] = {1, 4};
    
    // Act
    push_b(state);
    
    // Assert
    int result_a = check_stack_content(state->a, expected_a, 2);
    int result_b = check_stack_content(state->b, expected_b, 2);
    int result = result_a && result_b;
    print_test_result("PB (Push B)", result);
    
    free_sorting_state(state);
}

void test_push_operations(void)
{
    printf("📤 Testing Push Operations\n");
    printf("---------------------------\n");
    
    test_push_a();
    test_push_b();
    
    printf("\n");
}
