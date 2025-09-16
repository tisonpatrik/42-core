#include "../include/stack.h"
#include "../include/selector.h"
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
    test_snapshot_stack();
    test_apply_combined_iteration0();
    test_apply_combined_iteration1();
    test_apply_combined_iteration2();
    test_apply_combined_push_to_a();
    test_align_min_to_top_iteration0();
    test_align_min_to_top_iteration1();
    test_align_min_to_top_iteration2();
    test_align_min_to_top_simple_case();
    test_separator_large_input_function();
    
    printf("\n🧪 Running indexize_array Tests\n");
    printf("=====================================\n");
    test_indexize_array_basic_unique_values();
    test_indexize_array_single_element();
    test_indexize_array_all_same_values();
    test_indexize_array_already_sorted();
    test_indexize_array_reverse_sorted();
    test_indexize_array_negative_values();
    test_indexize_array_empty_array();
    test_indexize_array_null_input();
    test_indexize_array_negative_size();
    test_indexize_array_idempotent_property();
    test_indexize_array_user_specific_input();

    printf("\n🧪 Running find_target_position Tests\n");
    printf("=====================================\n");
    test_find_target_position_basic_case();
    
    printf("\n✨ All tests completed!\n");
    return 0;
}
