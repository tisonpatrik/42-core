/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:39:48 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:39:49 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"
#include <math.h>

t_v2d	ft_v2d_add(t_v2d a, t_v2d b)
{
	return ((t_v2d){a.x + b.x, a.y + b.y});
}

t_v2d	ft_v2d_sub(t_v2d a, t_v2d b)
{
	return ((t_v2d){a.x - b.x, a.y - b.y});
}

t_v2d	ft_v2d_scale(t_v2d vector, double scalar)
{
	return ((t_v2d){vector.x * scalar, vector.y * scalar});
}

t_v2d	ft_v2d_rotate(t_v2d vector, double angle)
{
	double	cosine;
	double	sine;

	cosine = cos(angle);
	sine = sin(angle);
	return ((t_v2d){vector.x * cosine - vector.y * sine,
		vector.x * sine + vector.y * cosine});
}

double	ft_v2d_length(t_v2d vector)
{
	return (sqrt(ft_v2d_length_squared(vector)));
}
