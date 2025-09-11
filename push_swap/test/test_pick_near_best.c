#include "test_main.h"
#include "../include/selector.h"

// Helper function to create test data
static void create_test_data(t_sorting_state *state, int *stack_a, int stack_a_size, int *stack_b, int stack_b_size)
{
    // Clear existing stacks
    clear_stack(state->a);
    clear_stack(state->b);
    
    // Fill stack A
    for (int i = 0; i < stack_a_size; i++) {
        t_node *node = create_node(stack_a[i]);
        push_to_stack(state->a, node);
    }
    
    // Fill stack B
    for (int i = 0; i < stack_b_size; i++) {
        t_node *node = create_node(stack_b[i]);
        push_to_stack(state->b, node);
    }
}

// Test function for SelectBestBtoAMove with all combinations of [1,2,3,4]
void test_select_best_b_to_a_move_all_combinations_1_2_3_4(void)
{
    printf("Running SelectBestBtoAMove All Combinations [1,2,3,4] test...\n");
    
    // All permutations of [1,2,3,4]
    int permutations[24][4] = {
        {1, 2, 3, 4}, {1, 2, 4, 3}, {1, 3, 2, 4}, {1, 3, 4, 2}, {1, 4, 2, 3}, {1, 4, 3, 2},
        {2, 1, 3, 4}, {2, 1, 4, 3}, {2, 3, 1, 4}, {2, 3, 4, 1}, {2, 4, 1, 3}, {2, 4, 3, 1},
        {3, 1, 2, 4}, {3, 1, 4, 2}, {3, 2, 1, 4}, {3, 2, 4, 1}, {3, 4, 1, 2}, {3, 4, 2, 1},
        {4, 1, 2, 3}, {4, 1, 3, 2}, {4, 2, 1, 3}, {4, 2, 3, 1}, {4, 3, 1, 2}, {4, 3, 2, 1}
    };
    
    int passed = 0;
    int failed = 0;
    int total_tests = 0;
    
    for (int perm_idx = 0; perm_idx < 24; perm_idx++) {
        for (int split_point = 1; split_point < 4; split_point++) {
            total_tests++;
            
            // Create stack A and B based on split point
            int stackA[4];
            int stackB[4];
            int stackA_size = split_point;
            int stackB_size = 4 - split_point;
            
            // Copy data to stack A
            for (int i = 0; i < stackA_size; i++) {
                stackA[i] = permutations[perm_idx][i];
            }
            
            // Copy data to stack B
            for (int i = 0; i < stackB_size; i++) {
                stackB[i] = permutations[perm_idx][split_point + i];
            }
            
            // Create SortingState with empty stacks
            t_sorting_state *state = malloc(sizeof(t_sorting_state));
            if (!state) {
                printf("❌ Failed to allocate memory for sorting state\n");
                failed++;
                continue;
            }
            state->a = create_stack();
            state->b = create_stack();
            state->operations = NULL;
            if (!state->a || !state->b) {
                printf("❌ Failed to create stacks\n");
                if (state->a) free(state->a);
                if (state->b) free(state->b);
                free(state);
                failed++;
                continue;
            }
            
            // Populate stacks with test data
            create_test_data(state, stackA, stackA_size, stackB, stackB_size);
            
            // Act - Call select_best_b_to_a_move
            t_position result = select_best_b_to_a_move(state, 30);
            
            // Assert - Verify the result is valid
            bool test_passed = true;
            
            // Check FromIndex validity
            if (result.from_index < 0 || result.from_index >= stackB_size) {
                printf("❌ FromIndex %d invalid for B size %d (permutation %d, split %d)\n", 
                       result.from_index, stackB_size, perm_idx, split_point);
                test_passed = false;
            }
            
            // Check ToIndex validity
            if (result.to_index < 0 || result.to_index > stackA_size) {
                printf("❌ ToIndex %d invalid for A size %d (permutation %d, split %d)\n", 
                       result.to_index, stackA_size, perm_idx, split_point);
                test_passed = false;
            }
            
            // Check Total cost validity
            if (result.total < 0) {
                printf("❌ Total cost %d should not be negative (permutation %d, split %d)\n", 
                       result.total, perm_idx, split_point);
                test_passed = false;
            }
            
            if (test_passed) {
                passed++;
            } else {
                failed++;
            }
            
            // Cleanup
            free_sorting_state(state);
        }
    }
    
    printf("Test Results: %d passed, %d failed out of %d total tests\n", passed, failed, total_tests);
    
    if (failed == 0) {
        printf("✅ All combinations test passed!\n");
    } else {
        printf("❌ Some combinations failed!\n");
    }
}