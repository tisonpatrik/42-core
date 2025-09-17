/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:32 by ptison            #+#    #+#             */
/*   Updated: 2025/09/17 21:11:17 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include "../../include/separator.h"
#include <stdbool.h>

static void	update_b_range(int value, int *min_b, int *max_b, bool *has_b_range)
{
	if (*has_b_range == false)
	{
		*min_b = value;
		*max_b = value;
		*has_b_range = true;
	}
	else
	{
		if (value < *min_b)
			*min_b = value;
		if (value > *max_b)
			*max_b = value;
	}
}

void	apply_shaping(t_sorting_state *state)
{
	static int	min_b = 0;
	static int	max_b = 0;
	static bool	has_b_range = false;
	int			mid;
	int			value;

	value = state->b->head->content;
	update_b_range(value, &min_b, &max_b, &has_b_range);
	mid = (min_b + max_b) / 2;
	if (value < mid)
	{
		rotate_b(state);
	}
}

void	process_stack_elements(t_sorting_state *state, int size_a,
		t_node **lis_nodes)
{
	int		i;
	t_node	*current;
	size_t	lis_count;

	lis_count = calculate_lis_length(lis_nodes);
	i = 0;
	while (i < size_a)
	{
		current = state->a->head;
		if (is_node_in_lis(current, lis_nodes, lis_count))
		{
			rotate_a(state);
		}
		else
		{
			push_b(state);
			apply_shaping(state);
		}
		i++;
	}
}

void	push_non_lis_into_b(t_sorting_state *state)
{
	t_separator_arena	*arena;
	t_node				**lis_nodes;
	int					size_a;

	if (!state || !state->a)
		return ;
	size_a = get_size(state->a);
	if (size_a <= 3)
		return ;
	arena = allocate_separator_arena(size_a);
	if (!arena)
		return ;
	lis_nodes = get_lis_nodes(state->a, arena);
	if (!lis_nodes)
	{
		free_separator_arena(arena);
		return ;
	}
	process_stack_elements(state, size_a, lis_nodes);
	free_separator_arena(arena);
}
