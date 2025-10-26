/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:25:36 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 18:32:07 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

static void	initialize_bresenham_state(t_bresenham_state *state,
		t_point2d start_point, t_point2d end_point)
{
	int	x_distance;
	int	y_distance;

	state->current_x = start_point.x;
	state->current_y = start_point.y;
	state->target_x = end_point.x;
	state->target_y = end_point.y;
	state->color = start_point.rgba;
	x_distance = abs(state->target_x - state->current_x);
	y_distance = abs(state->target_y - state->current_y);
	state->delta_x = x_distance;
	state->delta_y = -y_distance;
	if (state->current_x < state->target_x)
		state->step_x = 1;
	else
		state->step_x = -1;
	if (state->current_y < state->target_y)
		state->step_y = 1;
	else
		state->step_y = -1;
	state->error_accumulator = state->delta_x + state->delta_y;
}

static void	draw_current_pixel(mlx_image_t *image,
		const t_bresenham_state *state)
{
	size_t	pixel_index;

	if (state->current_x >= 0 && state->current_x < (int)image->width
		&& state->current_y >= 0 && state->current_y < (int)image->height)
	{
		pixel_index = (size_t)state->current_y * image->width
			+ state->current_x;
		((uint32_t *)image->pixels)[pixel_index] = state->color;
	}
}

static void	update_bresenham_state(t_bresenham_state *state)
{
	int	error_doubled;

	error_doubled = state->error_accumulator << 1;
	if (error_doubled >= state->delta_y)
	{
		state->error_accumulator += state->delta_y;
		state->current_x += state->step_x;
	}
	if (error_doubled <= state->delta_x)
	{
		state->error_accumulator += state->delta_x;
		state->current_y += state->step_y;
	}
}

void	draw_line_between_points(mlx_image_t *image, t_point2d start_point,
		t_point2d end_point)
{
	t_bresenham_state	state;

	initialize_bresenham_state(&state, start_point, end_point);
	while (true)
	{
		draw_current_pixel(image, &state);
		if (state.current_x == state.target_x
			&& state.current_y == state.target_y)
			break ;
		update_bresenham_state(&state);
	}
}
