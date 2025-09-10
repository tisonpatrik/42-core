/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:14:10 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:14:17 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

int	merged_cost(int a, int b)
{
	bool	same;

	same = (a >= 0 && b >= 0) || (a < 0 && b < 0);
	if (same)
	{
		if (ft_abs(a) > ft_abs(b))
			return (ft_abs(a));
		return (ft_abs(b));
	}
	return (ft_abs(a) + ft_abs(b));
}

int	signed_cost(int idx, int size)
{
	if (idx <= size / 2)
		return (idx);
	return (idx - size);
}
