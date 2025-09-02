#include "test_main.h"

// Test RA (Rotate A)
void test_rotate_a()
{
    // Arrange
    int numbers[] = {1, 2, 3};
    t_sorting_state *state = create_sorting_state(numbers, 3);
    int expected[] = {2, 3, 1};
    
    // Act
    rotate_a(state);
    
    // Assert
    int result = check_stack_content(state->a, expected, 3);
    print_test_result("RA (Rotate A)", result);
    
    free_sorting_state(state);
}

// Test RB (Rotate B)
void test_rotate_b()
{
    // Arrange
    int numbers[] = {4, 5, 6};
    t_sorting_state *state = create_sorting_state(numbers, 3);
    fill_stack(state->b, numbers, 3);
    clear_stack(state->a);
    int expected[] = {5, 6, 4};
    
    // Act
    rotate_b(state);
    
    // Assert
    int result = check_stack_content(state->b, expected, 3);
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

void test_rotate_operations(void)
{
    printf("🔄 Testing Rotate Operations\n");
    printf("------------------------------\n");
    
    test_rotate_a();
    test_rotate_b();
    test_rotate_ab();
    
    printf("\n");
}
