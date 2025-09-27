/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:24:20 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:18 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include "../../include/stack.h"

static void	get_three_values(t_stack *stack, int *first, int *second,
		int *third)
{
	t_node	*first_node;
	t_node	*second_node;
	t_node	*third_node;

	first_node = get_head(stack);
	second_node = get_next(first_node);
	third_node = get_next(second_node);
	*first = get_content(first_node);
	*second = get_content(second_node);
	*third = get_content(third_node);
}

static void	handle_sorting_cases(t_sorting_state *ps, int first, int second,
		int third)
{
	if (first > second && second < third && first < third)
	{
		swap_a(ps);
		return ;
	}
	if (first > second && second > third)
	{
		swap_a(ps);
		reverse_rotate_a(ps);
		return ;
	}
	if (first > second && second < third && first > third)
	{
		rotate_a(ps);
		return ;
	}
	if (first < second && second > third && first < third)
	{
		swap_a(ps);
		rotate_a(ps);
		return ;
	}
	reverse_rotate_a(ps);
}

void	sort_three(t_sorting_state *ps)
{
	int	first_value;
	int	second_value;
	int	third_value;

	if (get_size(ps->a) != 3)
		return ;
	get_three_values(ps->a, &first_value, &second_value, &third_value);
	if (first_value < second_value && second_value < third_value)
		return ;
	handle_sorting_cases(ps, first_value, second_value, third_value);
}
