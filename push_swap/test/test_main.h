#ifndef TEST_MAIN_H
# define TEST_MAIN_H

#include "../include/ops.h"
#include "../include/stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Test helper function declarations
void print_test_result(const char *test_name, int passed);
int check_stack_content(t_stack *stack, int *expected, int expected_size);

// Test function declarations
void test_swap_operations(void);
void test_push_operations(void);
void test_rotate_operations(void);
void test_reverse_rotate_operations(void);
void test_is_sorted_function(void);
void test_lis_operations(void);
void test_select_best_b_to_a_move_all_combinations_1_2_3_4(void);
void test_enumerate_b_to_a_iteration0(void);
void test_enumerate_a_to_b_iteration0(void);
void test_snapshot_stack_iteration0(void);
void test_snapshot_stack_empty_stack(void);
void test_snapshot_stack_single_element(void);
void test_apply_combined_iteration0(void);
void test_apply_combined_iteration1(void);
void test_apply_combined_iteration2(void);
void test_apply_combined_push_to_a(void);
void test_align_min_to_top_iteration0(void);
void test_align_min_to_top_iteration1(void);
void test_align_min_to_top_iteration2(void);
void test_align_min_to_top_simple_case(void);

#endif
