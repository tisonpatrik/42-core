/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:39:18 by ptison            #+#    #+#             */
/*   Updated: 2025/09/17 22:14:54 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>





int	merged_cost(int a, int b)
{
	int		cost_a;
	int		cost_b;
	bool	same_sign;

	cost_a = ft_abs(a);
	cost_b = ft_abs(b);
	same_sign = (a > 0 && b > 0) || (a < 0 && b < 0);
	if (same_sign)
	{
		if (cost_a > cost_b)
		{
			return (cost_a);
		}
		return (cost_b);
	}
	return (cost_a + cost_b);
}

int	signed_cost(int idx, int size)
{
	if (idx <= size / 2)
		return (idx);
	return (idx - size);
}



bool	is_better_position(t_position a, t_position b)
{
	if (a.total != b.total)
		return (a.total < b.total);
	if (ft_abs(a.cost_a) != ft_abs(b.cost_a))
		return (ft_abs(a.cost_a) < ft_abs(b.cost_a));
	if (a.to_index != b.to_index)
		return (a.to_index < b.to_index);
	return (a.from_index < b.from_index);
}
