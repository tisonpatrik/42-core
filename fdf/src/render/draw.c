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

static void draw_clear_fast(mlx_image_t* image, uint32_t color)
{
	size_t n = (size_t)image->width * image->height;
	uint32_t* p = (uint32_t*)image->pixels;
	for (size_t i = 0; i < n; ++i) p[i] = color;
}

void	draw_image_fast(mlx_image_t *image, t_grid *grid, t_camera *camera)
{
	draw_clear_fast(image, BACKGROUND);

	t_point2d_temp* pts = project_all(grid, camera);
	if (!pts) return;

	const int rows = grid->rows;
	const int cols = grid->cols;
	const int step = calculate_lod_step(rows, cols, camera->zoom);
	const int lod_rows = (rows + step - 1) / step;
	const int lod_cols = (cols + step - 1) / step;

	for (int y = 0; y < lod_rows; ++y)
	{
		for (int x = 0; x < lod_cols; ++x)
		{
			if (y + 1 < lod_rows)
				bresenham_fast(image, pts[(size_t)y * lod_cols + x],
				                        pts[(size_t)(y + 1) * lod_cols + x]);
			if (x + 1 < lod_cols)
				bresenham_fast(image, pts[(size_t)y * lod_cols + x],
				                        pts[(size_t)y * lod_cols + (x + 1)]);
		}
	}

	free(pts);
}

