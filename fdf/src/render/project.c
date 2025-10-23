/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:20:59 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 14:21:50 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

static void	project_grid_row(const t_grid *grid, t_camera *camera,
		t_point2d_temp *out, int y, int step, int lod_cols)
{
	int				x;
	t_point2d_temp	r;
	t_point3d		p3;
	double			tx;
	double			ty;
	double			tz;

	x = 0;
	while (x < grid->cols)
	{
		p3 = grid->grid3d[y][x];
		tx = p3.x;
		ty = p3.y;
		tz = p3.z * camera->zscale;
		rotate_z(&tx, &ty, camera->sin_zrot, camera->cos_zrot);
		rotate_x(&ty, &tz, camera->sin_xrot, camera->cos_xrot);
		rotate_y(&tx, &tz, camera->sin_yrot, camera->cos_yrot);
		r.x = (int)((tx * camera->zoom - ty * camera->zoom) * camera->cos_alpha
				+ camera->x_offset);
		r.y = (int)(-tz * camera->zoom + (tx * camera->zoom + ty * camera->zoom)
				* camera->sin_beta + camera->y_offset);
		r.rgba = p3.mapcolor;
		out[(size_t)(y / step) * lod_cols + (x / step)] = r;
		x += step;
	}
}

static t_point2d_temp	*project_all(const t_grid *grid, t_camera *camera)
{
	int				rows;
	int				cols;
	int				step;
	int				lod_rows;
	int				lod_cols;
	int				x;
	int				y;
	t_point2d_temp	*out;

	rows = grid->rows;
	cols = grid->cols;
	step = calculate_lod_step(rows, cols, camera->zoom);
	lod_rows = (rows + step - 1) / step;
	lod_cols = (cols + step - 1) / step;
	out = (t_point2d_temp *)malloc((size_t)lod_rows * lod_cols * sizeof(*out));
	if (!out)
		return (NULL);
	y = 0;
	while (y < rows)
	{
		project_grid_row(grid, camera, out, y, step, lod_cols);
		y += step;
	}
	return (out);
}

t_render_grid	create_render_grid(t_grid *grid, t_camera *camera)
{
	t_render_grid	render_grid;

	render_grid.points = project_all(grid, camera);
	if (!render_grid.points)
	{
		render_grid.step = 0;
		render_grid.rows = 0;
		render_grid.cols = 0;
		return (render_grid);
	}
	render_grid.step = calculate_lod_step(grid->rows, grid->cols, camera->zoom);
	render_grid.rows = (grid->rows + render_grid.step - 1) / render_grid.step;
	render_grid.cols = (grid->cols + render_grid.step - 1) / render_grid.step;
	return (render_grid);
}
