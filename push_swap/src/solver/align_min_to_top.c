/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align_min_to_top.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:01:47 by ptison            #+#    #+#             */
/*   Updated: 2025/09/17 20:56:33 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include "../../include/solver.h"

static int	find_min_index(t_stack *stack)
{
	int		min_index;
	int		min_value;
	int		current_index;
	t_node	*current_node;

	min_index = 0;
	min_value = get_content(get_head(stack));
	current_node = get_head(stack);
	current_index = 0;
	while (current_node != NULL)
	{
		if (get_content(current_node) < min_value)
		{
			min_value = get_content(current_node);
			min_index = current_index;
		}
		current_node = get_next(current_node);
		current_index++;
	}
	return (min_index);
}

static void	perform_rotations(t_sorting_state *ps, int cost)
{
	while (cost > 0)
	{
		rotate_a(ps);
		cost--;
	}
	while (cost < 0)
	{
		reverse_rotate_a(ps);
		cost++;
	}
}

void	align_min_to_top(t_sorting_state *ps)
{
	int	size_a;
	int	min_idx;
	int	cost;

	size_a = get_size(ps->a);
	if (size_a == 0)
		return ;
	min_idx = find_min_index(ps->a);
	cost = signed_cost(min_idx, size_a);
	perform_rotations(ps, cost);
}
