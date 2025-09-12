/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:32 by ptison            #+#    #+#             */
/*   Updated: 2025/09/12 03:05:45 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include "../../include/separator.h"
#include <stdlib.h>

void	update_b_range(int val, int *min_b, int *max_b, bool *has_b_range)
{
	if (!*has_b_range)
	{
		*min_b = val;
		*max_b = val;
		*has_b_range = true;
	}
	else
	{
		if (val < *min_b)
			*min_b = val;
		if (val > *max_b)
			*max_b = val;
	}
}

void	process_stack_elements(t_sorting_state *state, int size_a)
{
	int		min_b;
	int		max_b;
	bool	has_b_range;
	int		i;
	int		val;

	min_b = 0;
	max_b = 0;
	has_b_range = false;
	i = 0;
	while (i < size_a)
	{
		val = get_content(get_head(state->a));
		update_b_range(val, &min_b, &max_b, &has_b_range);
		if (val < (min_b + max_b) / 2)
			rotate_b(state);
		i++;
	}
}

void	push_non_lis_into_b(t_sorting_state *state)
{
	t_node_bool_array	*lis_nodes;
	int					size_a;

	if (!state || !state->a)
		return ;
	lis_nodes = get_lis_nodes(state->a);
	if (!lis_nodes)
		return ;
	size_a = get_size(state->a);
	if (size_a <= 3)
	{
		free(lis_nodes->items);
		free(lis_nodes);
		return ;
	}
	process_stack_elements(state, size_a);
	free(lis_nodes->items);
	free(lis_nodes);
}