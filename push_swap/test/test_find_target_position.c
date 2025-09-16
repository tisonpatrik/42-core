#include "test_main.h"
#include "../include/selector.h"

// TestFindTargetPosition_BasicCase tests the basic functionality of find_target_position
void test_find_target_position_basic_case(void)
{
    // Arrange - Test data from your debug output
    int array[] = {9, 13, 16, 24, 28, 30, 34, 39, 44, 46, 48, 54, 63, 73, 76, 78, 84, 90, 95, 7};
    int array_size = sizeof(array) / sizeof(array[0]);
    int target_value = 4;
    
    // Act - Call the function
    int result = find_target_position(array, array_size, target_value);
    
    // Assert - Verify the result
    // Expected: 19 (since 4 should be inserted at the end, and the function finds the minimum index)
    int expected = 19; // Index of value 7 (the minimum)
    
    bool test_passed = (result == expected);
    if (!test_passed) {
        printf("❌ Expected %d, got %d\n", expected, result);
    }
    
    print_test_result("test_find_target_position_basic_case", test_passed);
}

// TestFindTargetPosition_Value4Case tests the specific case you mentioned
void test_find_target_position_value_4_case(void)
{
    // Arrange - Test data from your debug output
    int array[] = {9, 13, 16, 24, 28, 30, 34, 39, 44, 46, 48, 54, 63, 73, 76, 78, 84, 90, 95, 7};
    int array_size = sizeof(array) / sizeof(array[0]);
    int target_value = 4;
    
    // Act - Call the function
    int result = find_target_position(array, array_size, target_value);
    
    // Assert - Verify the result
    // Based on your debug output, expected value is 19
    int expected = 19;
    
    bool test_passed = (result == expected);
    if (!test_passed) {
        printf("❌ Expected %d, got %d\n", expected, result);
        printf("Array: ");
        for (int i = 0; i < array_size; i++) {
            printf("%d ", array[i]);
        }
        printf("\nTarget value: %d\n", target_value);
    }
    
    print_test_result("test_find_target_position_value_4_case", test_passed);
}