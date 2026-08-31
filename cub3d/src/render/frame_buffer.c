/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:29:45 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:30:04 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "color.h"
#include "game.h"
#include "renderer.h"

void	render_background(t_game *game)
{
	size_t		half_size;
	t_rgba_view	view;

	half_size = (size_t)WINDOW_WIDTH * WINDOW_HEIGHT / 2;
	view = image_rgba_view(game->frame_buffer);
	ft_rgba_fill(ft_rgba_view_pixel(&view, 0, 0), half_size,
		game->rom->ceiling_color);
	ft_rgba_fill(ft_rgba_view_pixel(&view, 0, WINDOW_HEIGHT / 2), half_size,
		game->rom->floor_color);
}

void	blend_pixel(t_rgba_ref destination, t_rgba source)
{
	t_rgba	result;

	result = ft_rgba_source_over(source, ft_rgba_read(destination));
	ft_rgba_write(destination, result);
}
