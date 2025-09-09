/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:32 by ptison            #+#    #+#             */
/*   Updated: 2025/09/09 18:49:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include "../../include/separator.h"
#include <stdlib.h>

void	push_non_lis_into_b(t_sorting_state *state)
{
	t_node_bool_array	*lis_nodes;
	int					size_a;
	int					min_b;
	int					max_b;
	bool				has_b_range;
	int					i;
	int					val;
	int					mid;

	if (!state || !state->a)
		return ;
	lis_nodes = get_lis_nodes(state->a);
	if (!lis_nodes)
		return ;
	size_a = get_size(state->a);
	if (size_a <= 3)
		return ;
	min_b = 0;
	max_b = 0;
	has_b_range = false;
	i = 0;
	while (i < size_a)
	{
		val = get_content(get_head(state->a));
		if (!has_b_range)
		{
			min_b = val;
			max_b = val;
			has_b_range = true;
		}
		else
		{
			if (val < min_b)
				min_b = val;
			if (val > max_b)
				max_b = val;
		}
		mid = (min_b + max_b) / 2;
		if (val < mid)
		{
			rotate_b(state);
		}
	}
	free(lis_nodes->items);
	free(lis_nodes);
}
