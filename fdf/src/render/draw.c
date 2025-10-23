/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:47:57 by ptison            #+#    #+#             */
/*   Updated: 2025/10/13 23:02:21 by ptison            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

static void	draw_clear(mlx_image_t *image, uint32_t color)
{
	size_t		n;
	uint32_t	*p;

	n = (size_t)image->width * image->height;
	p = (uint32_t *)image->pixels;
	for (size_t i = 0; i < n; ++i)
		p[i] = color;
}

static void	draw_grid_row(mlx_image_t *image, t_render_grid *render_grid, int y)
{
	int	x;
		const size_t current_index = (size_t)y * render_grid->cols + x;
			const size_t bottom_index = (size_t)(y + 1) * render_grid->cols + x;
			const size_t right_index = (size_t)y * render_grid->cols + (x + 1);

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

static t_render_grid	create_render_grid(t_grid *grid, t_camera *camera)
{
	t_render_grid	rg;

	rg.points = project_all(grid, camera);
	if (!rg.points)
	{
		rg.step = 0;
		rg.rows = 0;
		rg.cols = 0;
		return (rg);
	}
	rg.step = calculate_lod_step(grid->rows, grid->cols, camera->zoom);
	rg.rows = (grid->rows + rg.step - 1) / rg.step;
	rg.cols = (grid->cols + rg.step - 1) / rg.step;
	return (rg);
}

void	draw_image(mlx_image_t *image, t_grid *grid, t_camera *camera)
{
	t_render_grid	render_grig;
	int				y;

	draw_clear(image, BACKGROUND);
	render_grig = create_render_grid(grid, camera);
	if (!render_grig.points)
		return ;
	y = 0;
	while (y < render_grig.rows)
	{
		draw_grid_row(image, &render_grig, y);
		y++;
	}
	free(render_grig.points);
}
