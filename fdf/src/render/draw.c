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
#include <stdbool.h>

static inline void putpx_fast(mlx_image_t* img, int x, int y, uint32_t col)
{
	((uint32_t*)img->pixels)[(size_t)y * img->width + x] = col;
}

static inline void draw_clear_fast(mlx_image_t* image, uint32_t color)
{
	size_t n = (size_t)image->width * image->height;
	uint32_t* p = (uint32_t*)image->pixels;
	for (size_t i = 0; i < n; ++i) p[i] = color;
}

// Cohen–Sutherland bitmask
enum {
	CS_LEFT   = 1 << 0,
	CS_RIGHT  = 1 << 1,
	CS_BOTTOM = 1 << 2,
	CS_TOP    = 1 << 3
};

static inline int cs_code(int x, int y, int w, int h)
{
	int code = 0;
	if (x < 0)     code |= CS_LEFT;
	else if (x >= w)  code |= CS_RIGHT;
	if (y < 0)     code |= CS_BOTTOM;
	else if (y >= h)  code |= CS_TOP;
	return code;
}

static inline bool clip_line_cs(t_point2d_temp *a, t_point2d_temp *b, int w, int h)
{
	int code_a = cs_code(a->x, a->y, w, h);
	int code_b = cs_code(b->x, b->y, w, h);

	for (;;)
	{
		// Both points inside window
		if ((code_a | code_b) == 0)
			return true;

		// Both points outside same region
		if ((code_a & code_b) != 0)
			return false;

		// Choose point outside window
		int code_out = code_a ? code_a : code_b;
		t_point2d_temp *p_out = code_a ? a : b;

		// Calculate intersection point
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

		// Update point and recalculate code
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
	t_point2d_temp* out = (t_point2d_temp*)malloc((size_t)rows * cols * sizeof(*out));
	if (!out) return NULL;

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < cols; ++x)
		{
			const t_point3d p3 = grid->grid3d[y][x];

			double tx = p3.x;
			double ty = p3.y;
			double tz = p3.z * camera->zscale;

			rotate_z(&tx, &ty, camera->zrotate);
			rotate_x(&ty, &tz, camera->xrotate);
			rotate_y(&tx, &tz, camera->yrotate);

			t_point2d_temp r;
			r.x    = (int)((tx * camera->zoom - ty * camera->zoom) * cos(camera->alpha) + camera->x_offset);
			r.y    = (int)(-tz * camera->zoom + (tx * camera->zoom + ty * camera->zoom) * sin(camera->beta) + camera->y_offset);
			r.rgba = p3.mapcolor;

			out[(size_t)y * cols + x] = r;
		}
	}
	return out;
}

static inline void bresenham_fast(mlx_image_t *image,
                                  t_point2d_temp a, t_point2d_temp b)
{
	const int w = (int)image->width;
	const int h = (int)image->height;

	// Přesný ořez – když nic nezbyde, skonči
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
		// Po ořezu už jsme v okně → bounds-check můžeš klidně vypustit
		t_point2d_temp cur = { .x = x0, .y = y0, .rgba = a.rgba };
		uint32_t col = get_color(cur, a, b);
		putpx_fast(image, x0, y0, col);

		if (x0 == x1 && y0 == y1) break;

		int e2 = err << 1;
		if (e2 >= dy) { err += dy; x0 += sx; }
		if (e2 <= dx) { err += dx; y0 += sy; }
	}
}

void	draw_reset(mlx_image_t *image)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < image->height)
	{
		j = 0;
		while (j < image->width)
		{
			mlx_put_pixel(image, j, i, BACKGROUND);
			j++;
		}
		i++;
	}
}

t_point2d_temp	project_point(t_point3d point, t_camera *camera)
{
	t_point2d_temp	result;
	double			temp_x;
	double			temp_y;
	double			temp_z;

	temp_x = point.x;
	temp_y = point.y;
	temp_z = point.z * camera->zscale;
	rotate_z(&temp_x, &temp_y, camera->zrotate);
	rotate_x(&temp_y, &temp_z, camera->xrotate);
	rotate_y(&temp_x, &temp_z, camera->yrotate);
	result.x = (int)((temp_x * camera->zoom - temp_y * camera->zoom)
			* cos(camera->alpha) + camera->x_offset);
	result.y = (int)(-temp_z * camera->zoom + (temp_x * camera->zoom + temp_y
				* camera->zoom) * sin(camera->beta) + camera->y_offset);
	result.rgba = point.mapcolor;
	return (result);
}

static void	bresenham(mlx_image_t *image, t_point3d a_3d, t_point3d b_3d,
		t_camera *camera)
{
	t_point2d_temp	a;
	t_point2d_temp	b;
	t_point2d_temp	cur;
	int				error[2];

	a = project_point(a_3d, camera);
	b = project_point(b_3d, camera);
	cur.x = a.x;
	cur.y = a.y;
	error[0] = abs(b.x - a.x) - abs(b.y - a.y);
	while (cur.x != b.x || cur.y != b.y)
	{
		if ((uint32_t)cur.x < image->width && (uint32_t)cur.y < image->height)
			mlx_put_pixel(image, cur.x, cur.y, get_color(cur, a, b));
		error[1] = 2 * error[0];
		if (error[1] > -abs(b.y - a.y))
		{
			error[0] -= abs(b.y - a.y);
			cur.x += (a.x < b.x);
			cur.x -= (b.x < a.x);
		}
		if (error[1] < abs(b.x - a.x))
		{
			error[0] += abs(b.x - a.x);
			cur.y += (a.y < b.y);
			cur.y -= (b.y < a.y);
		}
	}
}

static void	draw_line(mlx_image_t *image, t_grid *grid, int x, int y,
		t_camera *camera)
{
	t_point3d	*current;
	t_point3d	*right;
	t_point3d	*down;

	current = &(grid->grid3d[y][x]);
	if (y + 1 < grid->rows)
	{
		down = &(grid->grid3d[y + 1][x]);
		bresenham(image, *current, *down, camera);
	}
	if (x + 1 < grid->cols)
	{
		right = &(grid->grid3d[y][x + 1]);
		bresenham(image, *current, *right, camera);
	}
}

void	draw_image(mlx_image_t *image, t_grid *grid, t_camera *camera)
{
	int	i;
	int	j;

	draw_reset(image);
	i = -1;
	while (++i < grid->rows)
	{
		j = -1;
		while (++j < grid->cols)
			draw_line(image, grid, j, i, camera);
	}
}

void	draw_image_fast(mlx_image_t *image, t_grid *grid, t_camera *camera)
{
	// 1) rychlé vyčištění
	draw_clear_fast(image, BACKGROUND);

	t_point2d_temp* pts = project_all(grid, camera);
	if (!pts) return;

	const int rows = grid->rows;
	const int cols = grid->cols;

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < cols; ++x)
		{
			if (y + 1 < rows)
				bresenham_fast(image, pts[(size_t)y * cols + x],
				                        pts[(size_t)(y + 1) * cols + x]);

			if (x + 1 < cols)
				bresenham_fast(image, pts[(size_t)y * cols + x],
				                        pts[(size_t)y * cols + (x + 1)]);
		}
	}

	free(pts);
}

void	display_menu(mlx_t *mlx)
{
	int	x;
	int	y;

	x = 20;
	y = 20;
	mlx_put_string(mlx, "CONTROLS", x, y);
	mlx_put_string(mlx, "Zoom\t\t\t\t\t\t\t\t\t\tmouse scroll or -+", x, y
		+= 35);
	mlx_put_string(mlx, "Translate\t\t\t\t\tarrow keys", x, y += 20);
	mlx_put_string(mlx, "Scale z\t\t\t\t\t\t\ts + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate x\t\t\t\t\t\tx + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate y\t\t\t\t\t\ty + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate z\t\t\t\t\t\tz + </>", x, y += 20);
	mlx_put_string(mlx, "PROJECTION", x, y += 30);
	mlx_put_string(mlx, "Angle x\t\t\t\t\t\t\tq + </>", x, y += 25);
	mlx_put_string(mlx, "Angle y\t\t\t\t\t\t\tw + </>", x, y += 20);
	mlx_put_string(mlx, "Isometric\t\t\t\t\t1", x, y += 20);
	mlx_put_string(mlx, "Dimetric\t\t\t\t\t\t2", x, y += 20);
	mlx_put_string(mlx, "Trimetric\t\t\t\t\t3", x, y += 20);
	mlx_put_string(mlx, "RESET\t\t\t\t\t\t\t\t\t0", x, y += 30);
}
