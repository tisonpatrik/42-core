/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:20:59 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 10:13:01 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"


static t_point2d_temp* project_all(const t_grid* grid, t_camera* camera)
{
	int rows = grid->rows, cols = grid->cols;
	int step = calculate_lod_step(rows, cols, camera->zoom);
	int lod_rows = (rows + step - 1) / step;
	int lod_cols = (cols + step - 1) / step;
	
	t_point2d_temp* out = (t_point2d_temp*)malloc((size_t)lod_rows * lod_cols * sizeof(*out));
	if (!out) return NULL;

	for (int y = 0; y < rows; y += step)
	{
		for (int x = 0; x < cols; x += step)
		{
			const t_point3d p3 = grid->grid3d[y][x];

			double tx = p3.x;
			double ty = p3.y;
			double tz = p3.z * camera->zscale;

			rotate_z(&tx, &ty, camera->sin_zrot, camera->cos_zrot);
			rotate_x(&ty, &tz, camera->sin_xrot, camera->cos_xrot);
			rotate_y(&tx, &tz, camera->sin_yrot, camera->cos_yrot);

			t_point2d_temp r;
			r.x    = (int)((tx * camera->zoom - ty * camera->zoom) * camera->cos_alpha + camera->x_offset);
			r.y    = (int)(-tz * camera->zoom + (tx * camera->zoom + ty * camera->zoom) * camera->sin_beta + camera->y_offset);
			r.rgba = p3.mapcolor;

			out[(size_t)(y / step) * lod_cols + (x / step)] = r;
		}
	}
	return out;
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