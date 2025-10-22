/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:25:36 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 00:26:26 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

static void putpx_fast(mlx_image_t* img, int x, int y, uint32_t col)
{
	((uint32_t*)img->pixels)[(size_t)y * img->width + x] = col;
}


static int cs_code(int x, int y, int w, int h)
{
	int code = 0;
	if (x < 0)     code |= CLIP_LEFT;
	else if (x >= w)  code |= CLIP_RIGHT;
	if (y < 0)     code |= CLIP_BOTTOM;
	else if (y >= h)  code |= CLIP_TOP;
	return code;
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
		if (code_out & CLIP_TOP)
		{
			x = a->x + (b->x - a->x) * (h - 1 - a->y) / (b->y - a->y);
			y = h - 1;
		}
		else if (code_out & CLIP_BOTTOM)
		{
			x = a->x + (b->x - a->x) * (0 - a->y) / (b->y - a->y);
			y = 0;
		}
		else if (code_out & CLIP_RIGHT)
		{
			y = a->y + (b->y - a->y) * (w - 1 - a->x) / (b->x - a->x);
			x = w - 1;
		}
		else if (code_out & CLIP_LEFT)
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



void bresenham_fast(mlx_image_t *image,t_point2d_temp a, t_point2d_temp b)
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