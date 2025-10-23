/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lod_step.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:22:56 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 00:23:27 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

int	calculate_lod_step(int rows, int cols, double zoom)
{
	int	max_dim;
	int	base_step;
	int	final_step;

	max_dim = rows > cols ? rows : cols;
	if (max_dim < 50)
		base_step = 1;
	else if (max_dim < 150)
		base_step = 2;
	else if (max_dim < 300)
		base_step = 3;
	else
		base_step = 4;
	if (zoom >= 2.0)
		final_step = base_step / 2;
	else if (zoom >= 1.0)
		final_step = base_step;
	else if (zoom >= 0.5)
		final_step = base_step * 2;
	else
		final_step = base_step * 4;
	return (final_step < 1 ? 1 : final_step);
}
