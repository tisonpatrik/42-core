/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2d_basis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:39:40 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:39:41 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

bool	ft_v2d_basis_coordinates(t_v2d vector, t_v2d x_axis,
	t_v2d y_axis, t_v2d *coordinates)
{
	double	determinant;

	if (!coordinates)
		return (false);
	determinant = ft_v2d_cross(x_axis, y_axis);
	if (determinant == 0.0)
		return (false);
	coordinates->x = ft_v2d_cross(vector, y_axis) / determinant;
	coordinates->y = ft_v2d_cross(x_axis, vector) / determinant;
	return (true);
}
