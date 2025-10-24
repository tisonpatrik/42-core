/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:25:36 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 09:52:25 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

static t_bresenham_state	init_bresenham_state(t_point2d_temp a,
		t_point2d_temp b)
{
	t_bresenham_state	state;

	state.current_x = a.x;
	state.current_y = a.y;
	state.target_x = b.x;
	state.target_y = b.y;
	state.delta_x = abs(state.target_x - state.current_x);
	if (state.current_x < state.target_x)
		state.step_x = 1;
	else
		state.step_x = -1;
	state.delta_y = -abs(state.target_y - state.current_y);
	if (state.current_y < state.target_y)
		state.step_y = 1;
	else
		state.step_y = -1;
	state.error_accumulator = state.delta_x + state.delta_y;
	state.color = a.rgba;
	return (state);
}

void	draw_line_between_points(mlx_image_t *image, t_point2d_temp a,
		t_point2d_temp b)
{
	t_bresenham_state	state;
	int					e2;

	state = init_bresenham_state(a, b);
	while (true)
	{
		if (state.current_x >= 0 && state.current_x < (int)image->width
			&& state.current_y >= 0 && state.current_y < (int)image->height)
			((uint32_t *)image->pixels)[(size_t)state.current_y * image->width
				+ state.current_x] = state.color;
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
