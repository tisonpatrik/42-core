/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:52:37 by ptison            #+#    #+#             */
/*   Updated: 2025/09/09 18:53:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_main.h"

// Test SA (Swap A)
void	test_swap_a(void)
{
	int				numbers[] = {1, 2, 3};
	t_sorting_state	*state;
	int				expected[] = {2, 1, 3};
	int				result;

	// Arrange
	state = create_sorting_state(numbers, 3);
	// Act
	swap_a(state);
	// Assert
	result = check_stack_content(state->a, expected, 3);
	print_test_result("SA (Swap A)", result);
	free_sorting_state(state);
}

// Test SB (Swap B)
void	test_swap_b(void)
{
	int				numbers[] = {4, 5, 6};
	t_sorting_state	*state;
	int				expected[] = {5, 4, 6};
	int				result;

	// Arrange
	state = create_sorting_state(numbers, 3);
	fill_stack(state->b, numbers, 3);
	clear_stack(state->a);
	// Act
	swap_b(state);
	// Assert
	result = check_stack_content(state->b, expected, 3);
	print_test_result("SB (Swap B)", result);
	free_sorting_state(state);
}

// Test SS (Swap both)
void	test_swap_ab(void)
{
	int				numbers_a[] = {1, 2, 3};
	int				numbers_b[] = {4, 5, 6};
	t_sorting_state	*state;
	int				expected_a[] = {2, 1, 3};
	int				expected_b[] = {5, 4, 6};
	int				result_a;
	int				result_b;
	int				result;

	// Arrange
	state = create_sorting_state(numbers_a, 3);
	fill_stack(state->b, numbers_b, 3);
	// Act
	swap_ab(state);
	// Assert
	result_a = check_stack_content(state->a, expected_a, 3);
	result_b = check_stack_content(state->b, expected_b, 3);
	result = result_a && result_b;
	print_test_result("SS (Swap both)", result);
	free_sorting_state(state);
}

void	test_swap_operations(void)
{
	printf("🔄 Testing Swap Operations\n");
	printf("---------------------------\n");
	test_swap_a();
	test_swap_b();
	test_swap_ab();
	printf("\n");
}
