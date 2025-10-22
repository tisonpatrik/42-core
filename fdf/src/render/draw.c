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

static void putpx_fast(mlx_image_t* img, int x, int y, uint32_t col)
{
	((uint32_t*)img->pixels)[(size_t)y * img->width + x] = col;
}

static void draw_clear_fast(mlx_image_t* image, uint32_t color)
{
	size_t n = (size_t)image->width * image->height;
	uint32_t* p = (uint32_t*)image->pixels;
	for (size_t i = 0; i < n; ++i) p[i] = color;
}

enum {
	CS_LEFT   = 1 << 0,
	CS_RIGHT  = 1 << 1,
	CS_BOTTOM = 1 << 2,
	CS_TOP    = 1 << 3
};

static int cs_code(int x, int y, int w, int h)
{
	int code = 0;
	if (x < 0)     code |= CS_LEFT;
	else if (x >= w)  code |= CS_RIGHT;
	if (y < 0)     code |= CS_BOTTOM;
	else if (y >= h)  code |= CS_TOP;
	return code;
}

static int calculate_lod_step(int rows, int cols, double zoom)
{
	int max_dim = rows > cols ? rows : cols;
	
	// Base LOD based on grid size
	int base_step;
	if (max_dim < 50)
		base_step = 1;
	else if (max_dim < 150)
		base_step = 2;
	else if (max_dim < 300)
		base_step = 3;
	else
		base_step = 4;
	
	// Adjust for zoom - higher zoom = more detail (lower step)
	// At zoom 1.0: use base_step
	// At zoom 2.0: use base_step/2 (more detail)
	// At zoom 0.5: use base_step*2 (less detail)
	int final_step;
	if (zoom >= 2.0)
		final_step = base_step / 2;
	else if (zoom >= 1.0)
		final_step = base_step;
	else if (zoom >= 0.5)
		final_step = base_step * 2;
	else
		final_step = base_step * 4;
	
	// Ensure minimum step of 1
	return final_step < 1 ? 1 : final_step;
}

static bool clip_line_cs(t_point2d_temp *a, t_point2d_temp *b, int w, int h)
{
	int code_a = cs_code(a->x, a->y, w, h);
	int code_b = cs_code(b->x, b->y, w, h);

	for (;;)
	{
		if ((code_a | code_b) == 0)
			return true;

		if ((code_a & code_b) != 0)
			return false;

		int code_out = code_a ? code_a : code_b;
		t_point2d_temp *p_out = code_a ? a : b;

		int x, y;
		if (code_out & CS_TOP)
		{
			x = a->x + (b->x - a->x) * (h - 1 - a->y) / (b->y - a->y);
			y = h - 1;
		}
		else if (code_out & CS_BOTTOM)
		{
			x = a->x + (b->x - a->x) * (0 - a->y) / (b->y - a->y);
			y = 0;
		}
		else if (code_out & CS_RIGHT)
		{
			y = a->y + (b->y - a->y) * (w - 1 - a->x) / (b->x - a->x);
			x = w - 1;
		}
		else if (code_out & CS_LEFT)
		{
			y = a->y + (b->y - a->y) * (0 - a->x) / (b->x - a->x);
			x = 0;
		}

		p_out->x = x;
		p_out->y = y;
		if (p_out == a)
			code_a = cs_code(a->x, a->y, w, h);
		else
			code_b = cs_code(b->x, b->y, w, h);
	}
}


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

static void bresenham_fast(mlx_image_t *image,
                                  t_point2d_temp a, t_point2d_temp b)
{
	const int w = (int)image->width;
	const int h = (int)image->height;

	if (!clip_line_cs(&a, &b, w, h))
		return;

	int x0 = a.x, y0 = a.y;
	int x1 = b.x, y1 = b.y;

	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;

	for (;;)
	{
		putpx_fast(image, x0, y0, a.rgba);

		if (x0 == x1 && y0 == y1) break;

		int e2 = err << 1;
		if (e2 >= dy) { err += dy; x0 += sx; }
		if (e2 <= dx) { err += dx; y0 += sy; }
	}
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

