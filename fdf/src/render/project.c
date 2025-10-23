/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:20:59 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 00:23:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

t_point2d_temp	*project_all(const t_grid *grid, t_camera *camera)
{
	int				rows = grid->rows, cols;
	int				step;
	int				lod_rows;
	int				lod_cols;
	t_point2d_temp	*out;
			const t_point3d p3 = grid->grid3d[y][x];
	double			tx;
	double			ty;
	double			tz;
			t_point2d_temp r;

	rows = grid->rows, cols = grid->cols;
	step = calculate_lod_step(rows, cols, camera->zoom);
	lod_rows = (rows + step - 1) / step;
	lod_cols = (cols + step - 1) / step;
	out = (t_point2d_temp *)malloc((size_t)lod_rows * lod_cols * sizeof(*out));
	if (!out)
		return (NULL);
	for (int y = 0; y < rows; y += step)
	{
		for (int x = 0; x < cols; x += step)
		{
			tx = p3.x;
			ty = p3.y;
			tz = p3.z * camera->zscale;
			rotate_z(&tx, &ty, camera->sin_zrot, camera->cos_zrot);
			rotate_x(&ty, &tz, camera->sin_xrot, camera->cos_xrot);
			rotate_y(&tx, &tz, camera->sin_yrot, camera->cos_yrot);
			r.x = (int)((tx * camera->zoom - ty * camera->zoom)
					* camera->cos_alpha + camera->x_offset);
			r.y = (int)(-tz * camera->zoom + (tx * camera->zoom + ty
						* camera->zoom) * camera->sin_beta + camera->y_offset);
			r.rgba = p3.mapcolor;
			out[(size_t)(y / step) * lod_cols + (x / step)] = r;
		}
	}
	return (out);
}
