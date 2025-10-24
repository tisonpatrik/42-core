/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:20:59 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 18:25:27 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

static t_point2d	project_to_screen(t_point3d point_3d)
{
	t_point2d	screen_point;
	double		isometric_x;
	double		isometric_y;

	isometric_x = (point_3d.x - point_3d.y) * COS_45;
	isometric_y = -point_3d.z + (point_3d.x + point_3d.y) * SIN_30;
	screen_point.x = (int)(isometric_x + WIDTH / 2.0);
	screen_point.y = (int)(isometric_y + HEIGHT / 2.0);
	screen_point.rgba = point_3d.mapcolor;
	return (screen_point);
}

static void	project_grid_row(const t_grid *grid, t_point2d *output_points, int row_index)
{
	int			column_index;
	t_point3d	point_3d;
	size_t		output_index;
	t_point2d	projected_point;

	column_index = 0;
	while (column_index < grid->cols)
	{
		point_3d = grid->grid3d[row_index][column_index];
		output_index = (size_t)row_index * grid->cols + column_index;
		projected_point = project_to_screen(point_3d);
		output_points[output_index] = projected_point;
		column_index++;
	}
}

static void	project_all(const t_grid *grid, t_point2d *output_points)
{
	int	row_index;

	row_index = 0;
	while (row_index < grid->rows)
	{
		project_grid_row(grid, output_points, row_index);
		row_index++;
	}
}

t_render_grid	create_render_grid(t_grid *grid)
{
	t_render_grid	render_grid;

	render_grid = allocate_render_grid(grid->rows, grid->cols);
	if (!render_grid.points)
		return (render_grid);
	project_all(grid, render_grid.points);
	return (render_grid);
}
