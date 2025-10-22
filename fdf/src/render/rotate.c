/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:46:05 by ptison            #+#    #+#             */
/*   Updated: 2025/10/22 23:05:30 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

void	rotate_x(double *y, double *z, double sin_a, double cos_a)
{
	double	previous_y;

	previous_y = *y;
	*y = previous_y * cos_a + *z * sin_a;
	*z = -previous_y * sin_a + *z * cos_a;
}

void	rotate_y(double *x, double *z, double sin_b, double cos_b)
{
	double	previous_x;

	previous_x = *x;
	*x = previous_x * cos_b + *z * sin_b;
	*z = -previous_x * sin_b + *z * cos_b;
}

void	rotate_z(double *x, double *y, double sin_g, double cos_g)
{
	double	previous_x;
	double	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos_g - previous_y * sin_g;
	*y = previous_x * sin_g + previous_y * cos_g;
}
