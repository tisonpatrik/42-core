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

#endif
