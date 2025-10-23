/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:14:47 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 13:49:13 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

void	draw_grid_row(mlx_image_t *image, t_render_grid *render_grid, int y)
{
	int		x;
	size_t	current_index;
	size_t	bottom_index;
	size_t	right_index;

	x = 0;
	while (x < render_grid->cols)
	{
		current_index = (size_t)y * render_grid->cols + x;
		if (y + 1 < render_grid->rows)
		{
			bottom_index = (size_t)(y + 1) * render_grid->cols + x;
			draw_line_between_points(image, render_grid->points[current_index],
				render_grid->points[bottom_index]);
		}
		if (x + 1 < render_grid->cols)
		{
			right_index = (size_t)y * render_grid->cols + (x + 1);
			draw_line_between_points(image, render_grid->points[current_index],
				render_grid->points[right_index]);
		}
		x++;
	}
}
