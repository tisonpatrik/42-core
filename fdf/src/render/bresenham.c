/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:25:36 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 09:49:26 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

static void	set_pixel_color(mlx_image_t *img, int x, int y, uint32_t col)
{
	((uint32_t *)img->pixels)[(size_t)y * img->width + x] = col;
}

static int	calculate_clip_code(int x, int y, int w, int h)
{
	int	code;

	code = 0;
	if (x < 0)
		code |= CLIP_LEFT;
	else if (x >= w)
		code |= CLIP_RIGHT;
	if (y < 0)
		code |= CLIP_BOTTOM;
	else if (y >= h)
		code |= CLIP_TOP;
	return (code);
}

static bool	clip_line_to_viewport(t_point2d_temp *a, t_point2d_temp *b, int w,
		int h)
{
	int				code_a;
	int				code_b;
	int				code_out;
	t_point2d_temp	*p_out;

	code_a = calculate_clip_code(a->x, a->y, w, h);
	code_b = calculate_clip_code(b->x, b->y, w, h);
	for (;;)
	{
		if ((code_a | code_b) == 0)
			return (true);
		if ((code_a & code_b) != 0)
			return (false);
		code_out = code_a ? code_a : code_b;
		p_out = code_a ? a : b;
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
			code_a = calculate_clip_code(a->x, a->y, w, h);
		else
			code_b = calculate_clip_code(b->x, b->y, w, h);
	}
}

void	draw_line_between_points(mlx_image_t *image, t_point2d_temp a,
		t_point2d_temp b)
{
	const int	w = (int)image->width;
	const int	h = (int)image->height;
	int			x0 = a.x, y0;
	int			x1 = b.x, y1;
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			err;
	int			e2;

	if (!clip_line_to_viewport(&a, &b, w, h))
		return ;
	x0 = a.x, y0 = a.y;
	x1 = b.x, y1 = b.y;
	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	for (;;)
	{
		set_pixel_color(image, x0, y0, a.rgba);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = err << 1;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
