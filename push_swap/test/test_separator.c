#include "test_main.h"
#include "../include/separator.h"

// Test separator with large input from launch.json args
void test_separator_large_input()
{
    // Arrange - Create input from launch.json args
    // Log line: test_separator_large_input.c:8 - Original numbers from launch.json
    int numbers[] = {77, 25, 55, 16, 52, 24, 28, 83, 4, 71, 85, 98, 89, 99, 30, 68, 92, 59, 6, 17, 91, 34, 86, 47, 8, 3, 57, 39, 65, 44, 69, 23, 80, 50, 60, 56, 46, 27, 21, 48, 54, 63, 42, 20, 73, 35, 97, 93, 11, 10, 22, 18, 87, 2, 96, 15, 72, 45, 29, 38, 49, 67, 79, 41, 94, 76, 36, 19, 5, 33, 12, 14, 40, 88, 78, 1, 84, 90, 58, 32, 61, 70, 43, 0, 82, 95, 9, 26, 75, 13, 53, 31, 37, 64, 62, 66, 74, 81, 7, 51};
    int input_size = sizeof(numbers) / sizeof(numbers[0]);
    
    // Expected results after separator
    int expected_a[] = {16, 24, 28, 30, 34, 39, 44, 46, 48, 54, 63, 73, 76, 78, 84, 90, 95};
    int expected_b[] = {51, 81, 74, 66, 62, 64, 53, 75, 82, 70, 61, 58, 88, 94, 79, 67, 72, 96, 87, 93, 97, 56, 60, 80, 69, 65, 57, 86, 91, 59, 92, 68, 99, 89, 98, 85, 71, 83, 52, 55, 77, 25, 4, 6, 17, 47, 8, 3, 23, 50, 27, 21, 42, 20, 35, 11, 10, 22, 18, 2, 15, 45, 29, 38, 49, 41, 36, 19, 5, 33, 12, 14, 40, 1, 32, 43, 0, 9, 26, 13, 31, 37, 7};
    
    t_sorting_state *state = create_sorting_state(numbers, input_size);
    
    // Act
    push_non_lis_into_b(state);
    
    // Assert
    int passed_a = check_stack_content(state->a, expected_a, sizeof(expected_a) / sizeof(expected_a[0]));
    int passed_b = check_stack_content(state->b, expected_b, sizeof(expected_b) / sizeof(expected_b[0]));
    int passed = (passed_a && passed_b);
    
    print_test_result("separator - large input from launch.json", passed);
    
    // Cleanup
    clear_stack(state->a);
    clear_stack(state->b);
    free(state->a);
    free(state->b);
    free(state);
}

void test_separator_large_input_function(void)
{
    test_separator_large_input();
}
