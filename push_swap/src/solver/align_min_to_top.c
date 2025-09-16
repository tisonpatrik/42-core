/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align_min_to_top.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:01:47 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 21:08:34 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include "../../include/solver.h"

void	align_min_to_top(t_sorting_state *ps)
{
	int		size_a;
	int		min_idx;
	int		min_val;
	int		cost;
	int		i;
	t_node	*n;

	size_a = get_size(ps->a);
	if (size_a == 0)
		return ;
	min_idx = 0;
	min_val = get_content(get_head(ps->a));
	n = get_head(ps->a);
	i = 0;
	while (n != NULL)
	{
		if (get_content(n) < min_val)
		{
			min_val = get_content(n);
			min_idx = i;
		}
		n = get_next(n);
		i++;
	}
	cost = signed_cost(min_idx, size_a);
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

