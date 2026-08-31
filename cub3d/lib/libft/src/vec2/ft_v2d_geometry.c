/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2d_geometry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:39:45 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:39:46 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"
#include <math.h>

double	ft_v2d_length_squared(t_v2d vector)
{
	return (vector.x * vector.x + vector.y * vector.y);
}

double	ft_v2d_distance_squared(t_v2d a, t_v2d b)
{
	return (ft_v2d_length_squared(ft_v2d_sub(a, b)));
}

double	ft_v2d_cross(t_v2d a, t_v2d b)
{
	return (a.x * b.y - a.y * b.x);
}

t_v2d	ft_v2d_perpendicular(t_v2d vector)
{
	return ((t_v2d){-vector.y, vector.x});
}

bool	ft_v2d_is_finite(t_v2d vector)
{
	return (isfinite(vector.x) && isfinite(vector.y));
}
