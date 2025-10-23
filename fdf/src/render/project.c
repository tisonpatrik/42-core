/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:20:59 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 15:24:40 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

static void	apply_rotations(t_point3d *p3, double *tz, t_camera *camera)
{
	rotate_z(&p3->x, &p3->y, camera->sin_zrot, camera->cos_zrot);
	rotate_x(&p3->y, tz, camera->sin_xrot, camera->cos_xrot);
	rotate_y(&p3->x, tz, camera->sin_yrot, camera->cos_yrot);
}

static t_point2d_temp	project_to_screen(t_point3d p3, double tz,
		t_camera *camera)
{
	t_point2d_temp	r;

	r.x = (int)((p3.x * camera->zoom - p3.y * camera->zoom) * camera->cos_alpha
			+ camera->x_offset);
	r.y = (int)(-tz * camera->zoom + (p3.x * camera->zoom + p3.y * camera->zoom)
			* camera->sin_beta + camera->y_offset);
	r.rgba = p3.mapcolor;
	return (r);
}

static void	project_grid_row(const t_grid *grid, t_camera *camera,
		t_point2d_temp *out, t_lod_params lod)
{
	int				x;
	t_point3d		p3;
	double			tz;
	size_t			output_index;
	t_point2d_temp	projected_point;

	x = 0;
	while (x < grid->cols)
	{
		p3 = grid->grid3d[lod.y][x];
		tz = p3.z * camera->zscale;
		apply_rotations(&p3, &tz, camera);
		output_index = (size_t)(lod.y / lod.step) * lod.lod_cols + (x
				/ lod.step);
		projected_point = project_to_screen(p3, tz, camera);
		out[output_index] = projected_point;
		x += lod.step;
	}
}

static t_point2d_temp	*project_all(const t_grid *grid, t_camera *camera)
{
	int				step;
	int				lod_rows;
	int				lod_cols;
	int				y;
	t_point2d_temp	*out;

	step = calculate_lod_step(grid->rows, grid->cols, camera->zoom);
	lod_rows = (grid->rows + step - 1) / step;
	lod_cols = (grid->cols + step - 1) / step;
	out = (t_point2d_temp *)malloc((size_t)lod_rows * lod_cols * sizeof(*out));
	if (!out)
		return (NULL);
	y = 0;
	while (y < grid->rows)
	{
		project_grid_row(grid, camera, out, (t_lod_params){step, lod_cols, y});
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
