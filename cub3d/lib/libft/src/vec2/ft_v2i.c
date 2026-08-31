/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2i.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:39:50 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:39:51 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

t_v2i	ft_v2i_add(t_v2i a, t_v2i b)
{
	return ((t_v2i){a.x + b.x, a.y + b.y});
}

t_v2i	ft_v2i_sub(t_v2i a, t_v2i b)
{
	return ((t_v2i){a.x - b.x, a.y - b.y});
}

double	ft_v2i_distance_squared(t_v2i a, t_v2i b)
{
	double	x;
	double	y;

	x = (double)a.x - b.x;
	y = (double)a.y - b.y;
	return (x * x + y * y);
}

bool	ft_v2i_equal(t_v2i a, t_v2i b)
{
	return (a.x == b.x && a.y == b.y);
}

t_v2d	ft_v2i_to_v2d(t_v2i vector)
{
	return ((t_v2d){vector.x, vector.y});
}
