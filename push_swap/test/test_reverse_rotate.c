/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reverse_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:51:42 by ptison            #+#    #+#             */
/*   Updated: 2025/09/09 18:51:45 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_main.h"

// Test RRA (Reverse rotate A)
void	test_reverse_rotate_a(void)
{
	int				numbers[] = {1, 2, 3};
	t_sorting_state	*state;
	int				expected[] = {3, 1, 2};
	int				result;

	// Arrange
	state = create_sorting_state(numbers, 3);
	// Act
	reverse_rotate_a(state);
	// Assert
	result = check_stack_content(state->a, expected, 3);
	print_test_result("RRA (Reverse rotate A)", result);
	free_sorting_state(state);
}

// Test RRB (Reverse rotate B)
void	test_reverse_rotate_b(void)
{
	int				numbers[] = {4, 5, 6};
	t_sorting_state	*state;
	int				expected[] = {6, 4, 5};
	int				result;

	// Arrange
	state = create_sorting_state(numbers, 3);
	fill_stack(state->b, numbers, 3);
	clear_stack(state->a);
	// Act
	reverse_rotate_b(state);
	// Assert
	result = check_stack_content(state->b, expected, 3);
	print_test_result("RRB (Reverse rotate B)", result);
	free_sorting_state(state);
}

// Test RRR (Reverse rotate both)
void	test_reverse_rotate_ab(void)
{
	int				numbers_a[] = {1, 2, 3};
	int				numbers_b[] = {4, 5, 6};
	t_sorting_state	*state;
	int				expected_a[] = {3, 1, 2};
	int				expected_b[] = {6, 4, 5};
	int				result_a;
	int				result_b;
	int				result;

	// Arrange
	state = create_sorting_state(numbers_a, 3);
	fill_stack(state->b, numbers_b, 3);
	// Act
	reverse_rotate_ab(state);
	// Assert
	result_a = check_stack_content(state->a, expected_a, 3);
	result_b = check_stack_content(state->b, expected_b, 3);
	result = result_a && result_b;
	print_test_result("RRR (Reverse rotate both)", result);
	free_sorting_state(state);
}

void	test_reverse_rotate_operations(void)
{
	printf("🔄 Testing Reverse Rotate Operations\n");
	printf("------------------------------------\n");
	test_reverse_rotate_a();
	test_reverse_rotate_b();
	test_reverse_rotate_ab();
	printf("\n");
}
