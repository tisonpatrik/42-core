#include "../include/validator.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "test_main.h"

// Helper function to compare two arrays
static int arrays_equal(const int *arr1, const int *arr2, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr1[i] != arr2[i])
            return 0;
    }
    return 1;
}

// Helper function to print array for debugging
static void print_array(const int *arr, int n, const char *name)
{
    printf("%s: [", name);
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("]\n");
}

// Test case: Basic functionality with unique values
void test_indexize_array_basic_unique_values(void)
{
    // Arrange
    int values[] = {5, 2, 8, 1, 9};
    int n = 5;
    int expected[] = {2, 1, 3, 0, 4}; // sorted: [1,2,5,8,9] -> indices: [0,1,2,3,4]
    
    // Act
    int *result = indexize_array(values, n);
    
    // Assert
    int passed = (result != NULL) && arrays_equal(result, expected, n);
    print_test_result("test_indexize_array_basic_unique_values", passed);
    
    if (!passed && result)
    {
        printf("Expected: ");
        print_array(expected, n, "");
        printf("Got:      ");
        print_array(result, n, "");
    }
    
    free(result);
}

// Test case: Single element
void test_indexize_array_single_element(void)
{
    // Arrange
    int values[] = {42};
    int n = 1;
    int expected[] = {0};
    
    // Act
    int *result = indexize_array(values, n);
    
    // Assert
    int passed = (result != NULL) && arrays_equal(result, expected, n);
    print_test_result("test_indexize_array_single_element", passed);
    
    free(result);
}

// Test case: All same values
void test_indexize_array_all_same_values(void)
{
    // Arrange
    int values[] = {7, 7, 7, 7};
    int n = 4;
    int expected[] = {0, 0, 0, 0};
    
    // Act
    int *result = indexize_array(values, n);
    
    // Assert
    int passed = (result != NULL) && arrays_equal(result, expected, n);
    print_test_result("test_indexize_array_all_same_values", passed);
    
    free(result);
}

// Test case: Already sorted array
void test_indexize_array_already_sorted(void)
{
    // Arrange
    int values[] = {1, 2, 3, 4, 5};
    int n = 5;
    int expected[] = {0, 1, 2, 3, 4};
    
    // Act
    int *result = indexize_array(values, n);
    
    // Assert
    int passed = (result != NULL) && arrays_equal(result, expected, n);
    print_test_result("test_indexize_array_already_sorted", passed);
    
    free(result);
}

// Test case: Reverse sorted array
void test_indexize_array_reverse_sorted(void)
{
    // Arrange
    int values[] = {5, 4, 3, 2, 1};
    int n = 5;
    int expected[] = {4, 3, 2, 1, 0};
    
    // Act
    int *result = indexize_array(values, n);
    
    // Assert
    int passed = (result != NULL) && arrays_equal(result, expected, n);
    print_test_result("test_indexize_array_reverse_sorted", passed);
    
    free(result);
}

// Test case: Negative values
void test_indexize_array_negative_values(void)
{
    // Arrange
    int values[] = {-3, 1, -1, 0, 2};
    int n = 5;
    int expected[] = {0, 3, 1, 2, 4}; // sorted: [-3,-1,0,1,2] -> indices: [0,1,2,3,4]
    
    // Act
    int *result = indexize_array(values, n);
    
    // Assert
    int passed = (result != NULL) && arrays_equal(result, expected, n);
    print_test_result("test_indexize_array_negative_values", passed);
    
    if (!passed && result)
    {
        printf("Expected: ");
        print_array(expected, n, "");
        printf("Got:      ");
        print_array(result, n, "");
    }
    
    free(result);
}

// Test case: Edge case - empty array (should return NULL)
void test_indexize_array_empty_array(void)
{
    // Arrange
    int n = 0;
    
    // Act
    int *result = indexize_array(NULL, n);
    
    // Assert
    int passed = (result == NULL);
    print_test_result("test_indexize_array_empty_array", passed);
}

// Test case: Edge case - NULL input (should return NULL)
void test_indexize_array_null_input(void)
{
    // Arrange
    int n = 5;
    
    // Act
    int *result = indexize_array(NULL, n);
    
    // Assert
    int passed = (result == NULL);
    print_test_result("test_indexize_array_null_input", passed);
}

// Test case: Edge case - negative size (should return NULL)
void test_indexize_array_negative_size(void)
{
    // Arrange
    int values[] = {1, 2, 3};
    int n = -1;
    
    // Act
    int *result = indexize_array(values, n);
    
    // Assert
    int passed = (result == NULL);
    print_test_result("test_indexize_array_negative_size", passed);
}

// Test case: Idempotent property - applying indexize twice should give same result
void test_indexize_array_idempotent_property(void)
{
    // Arrange
    int values[] = {5, 2, 8, 1, 9};
    int n = 5;
    
    // Act
    int *result1 = indexize_array(values, n);
    int *result2 = NULL;
    if (result1)
    {
        result2 = indexize_array(result1, n);
    }
    
    // Assert
    int passed = (result1 != NULL) && (result2 != NULL) && arrays_equal(result1, result2, n);
    print_test_result("test_indexize_array_idempotent_property", passed);
    
    free(result1);
    free(result2);
}

// Test case: Specific input from user - should stay the same when applied twice
void test_indexize_array_user_specific_input(void)
{
    // Arrange
    int values[] = {3, 5, 2, 6, 1, 4, 0, 7, 9, 8, 10};
    int n = 11;
    
    // Act - apply indexize_array twice
    int *result1 = indexize_array(values, n);
    int *result2 = NULL;
    if (result1)
    {
        result2 = indexize_array(result1, n);
    }
    
    // Assert - results should be identical (idempotent property)
    int passed = (result1 != NULL) && (result2 != NULL) && arrays_equal(result1, result2, n);
    print_test_result("test_indexize_array_user_specific_input", passed);
    
    if (!passed && result1 && result2)
    {
        printf("First application: ");
        print_array(result1, n, "");
        printf("Second application: ");
        print_array(result2, n, "");
    }
    else if (result1)
    {
        printf("Result: ");
        print_array(result1, n, "");
    }
    
    free(result1);
    free(result2);
}


