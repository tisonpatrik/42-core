#include "test_main.h"

// Test is_sorted with sorted stack
void test_is_sorted_sorted_stack()
{
    // Arrange - Create a sorted stack [1, 2, 3, 4, 5]
    // Log line: test_is_sorted.c:25 - Original numbers: [1, 2, 3, 4, 5]
    int numbers[] = {1, 2, 3, 4, 5};
    t_stack *stack = create_stack();
    fill_stack(stack, numbers, 5);
    
    // Act
    bool result = is_sorted(stack);
    
    // Assert
    int passed = (result == true);
    print_test_result("is_sorted - sorted stack", passed);
    
    clear_stack(stack);
    free(stack);
}

// Test is_sorted with unsorted stack
void test_is_sorted_unsorted_stack()
{
    // Arrange - Create an unsorted stack [3, 1, 4, 2, 5]
    // Log line: test_is_sorted.c:42 - Original numbers: [3, 1, 4, 2, 5]
    int numbers[] = {3, 1, 4, 2, 5};
    t_stack *stack = create_stack();
    fill_stack(stack, numbers, 5);
    
    // Act
    bool result = is_sorted(stack);
    
    // Assert
    int passed = (result == false);
    print_test_result("is_sorted - unsorted stack", passed);
    
    clear_stack(stack);
    free(stack);
}

void test_is_sorted_function(void)
{
    printf("📊 Testing is_sorted Function\n");
    printf("-------------------------------\n");
    
    test_is_sorted_sorted_stack();
    test_is_sorted_unsorted_stack();
    
    printf("\n");
}
