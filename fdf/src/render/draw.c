/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:14:47 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 10:15:09 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

void	draw_grid_row(mlx_image_t *image, t_render_grid *render_grid, int y)
{
	int		x;
	size_t	current_index;
	size_t	bottom_index;
	size_t	right_index;

	current_index = (size_t)y * render_grid->cols + x;
	bottom_index = (size_t)(y + 1) * render_grid->cols + x;
	right_index = (size_t)y * render_grid->cols + (x + 1);
	x = 0;
	while (x < render_grid->cols)
	{
		if (y + 1 < render_grid->rows)
		{
			draw_line_between_points(image, render_grid->points[current_index],
				render_grid->points[bottom_index]);
		}
		if (x + 1 < render_grid->cols)
		{
			draw_line_between_points(image, render_grid->points[current_index],
				render_grid->points[right_index]);
		}
		x++;
	}
}
