/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:25:36 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 19:45:02 by ptison           ###   ########.fr       */
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
	while (true)
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

static t_bresenham_state	init_bresenham_state(t_point2d_temp a,
		t_point2d_temp b)
{
	t_bresenham_state	state;

	state.current_x = a.x;
	state.current_y = a.y;
	state.target_x = b.x;
	state.target_y = b.y;
	state.delta_x = abs(state.target_x - state.current_x);
	state.step_x = state.current_x < state.target_x ? 1 : -1;
	state.delta_y = -abs(state.target_y - state.current_y);
	state.step_y = state.current_y < state.target_y ? 1 : -1;
	state.error_accumulator = state.delta_x + state.delta_y;
	state.color = a.rgba;
	return (state);
}

void	draw_line_between_points(mlx_image_t *image, t_point2d_temp a,
		t_point2d_temp b)
{
	int					w;
	int					h;
	t_bresenham_state	state;
	int					e2;

	w = (int)image->width;
	h = (int)image->height;
	if (!clip_line_to_viewport(&a, &b, w, h))
		return ;
	state = init_bresenham_state(a, b);
	for (;;)
	{
		set_pixel_color(image, state.current_x, state.current_y, state.color);
		if (state.current_x == state.target_x
			&& state.current_y == state.target_y)
			break ;
		e2 = state.error_accumulator << 1;
		if (e2 >= state.delta_y)
		{
			state.error_accumulator += state.delta_y;
			state.current_x += state.step_x;
		}
		if (e2 <= state.delta_x)
		{
			state.error_accumulator += state.delta_x;
			state.current_y += state.step_y;
		}
	}
}
