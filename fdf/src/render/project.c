/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:20:59 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 16:15:06 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

static t_point2d	project_to_screen(t_point3d p3)
{
	t_point2d	r;
	double		cos_alpha;
	double		sin_beta;

	cos_alpha = cos(45 * M_PI / 180);
	sin_beta = sin(30 * M_PI / 180);
	r.x = (int)((p3.x - p3.y) * cos_alpha + WIDTH / 2.0);
	r.y = (int)(-p3.z + (p3.x + p3.y) * sin_beta + HEIGHT / 2.0);
	r.rgba = p3.mapcolor;
	return (r);
}

static void	project_grid_row(const t_grid *grid, t_point2d *out, int y)
{
	int			x;
	t_point3d	p3;
	size_t		output_index;
	t_point2d	projected_point;

	x = 0;
	while (x < grid->cols)
	{
		p3 = grid->grid3d[y][x];
		output_index = (size_t)y * grid->cols + x;
		projected_point = project_to_screen(p3);
		out[output_index] = projected_point;
		x++;
	}
}

static t_point2d	*project_all(const t_grid *grid)
{
	int			y;
	t_point2d	*out;

	out = (t_point2d *)malloc((size_t)grid->rows * grid->cols * sizeof(*out));
	if (!out)
		return (NULL);
	y = 0;
	while (y < grid->rows)
	{
		project_grid_row(grid, out, y);
		y++;
	}
	return (out);
}

t_render_grid	create_render_grid(t_grid *grid)
{
	t_render_grid	render_grid;

	render_grid.points = project_all(grid);
	if (!render_grid.points)
	{
		render_grid.rows = 0;
		render_grid.cols = 0;
		return (render_grid);
	}
	render_grid.rows = grid->rows;
	render_grid.cols = grid->cols;
	return (render_grid);
}
