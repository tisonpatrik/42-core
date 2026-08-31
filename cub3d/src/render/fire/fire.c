/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:29:16 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:29:17 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "color.h"
#include "config.h"
#include "ft_math.h"
#include "game.h"
#include "fire.h"

static bool	project_fire(t_draw *draw, double distance, double height)
{
	int	full_start;
	int	height_shift;

	draw->projected_height = (int)(WINDOW_HEIGHT / distance);
	if (draw->projected_height < 1)
		return (false);
	full_start = WINDOW_HEIGHT / 2 - draw->projected_height / 2;
	height_shift = (int)(draw->projected_height * (1.0 - height));
	draw->screen_top = full_start + height_shift;
	draw->screen_bottom = WINDOW_HEIGHT / 2 + draw->projected_height / 2;
	draw->screen_top = ft_max_int(draw->screen_top, 0);
	draw->screen_bottom = ft_clamp_int(draw->screen_bottom, 0,
			WINDOW_HEIGHT - 1);
	draw->texture_y_position = draw->screen_top - full_start - height_shift;
	return (true);
}

static bool	init_fire_draw(t_game *game, t_ray *ray, t_ray_hit *hit,
	t_draw *draw)
{
	double	height;
	double	distance;

	height = fire_height_at(game, hit->map);
	if (height <= 0.0)
		return (false);
	distance = hit->distance;
	if (distance < FIRE_MIN_DISTANCE)
		distance = FIRE_MIN_DISTANCE;
	if (!project_fire(draw, distance, height))
		return (false);
	draw->texture_x = texture_column(hit, ray->dir,
			(int)game->rom->textures.fire->width);
	draw->texture_y_step = (double)game->rom->textures.fire->width
		/ draw->projected_height;
	draw->texture_y_position *= draw->texture_y_step;
	return (true);
}

static void	draw_fire_pixels(t_game *game, int x, t_draw *draw, int frame)
{
	mlx_texture_t	*texture;
	t_rgba_view		destination;
	t_rgba_view		source;
	t_rgba			color;
	int				tex_y;

	texture = game->rom->textures.fire;
	destination = image_rgba_view(game->frame_buffer);
	source = texture_rgba_view(texture);
	while (draw->screen_top <= draw->screen_bottom)
	{
		tex_y = (int)draw->texture_y_position;
		tex_y = ft_clamp_int(tex_y, 0, (int)texture->width - 1);
		color = ft_rgba_read(ft_rgba_view_pixel(&source, draw->texture_x,
					(int)((size_t)frame * texture->width + (size_t)tex_y)));
		if (color.alpha > FIRE_ALPHA_THRESHOLD)
			blend_pixel(ft_rgba_view_pixel(&destination, x,
					draw->screen_top), color);
		draw->texture_y_position += draw->texture_y_step;
		draw->screen_top++;
	}
}

void	draw_fire_column(t_game *game, int x, t_ray *ray, t_ray_hit *hit)
{
	t_draw		draw;
	int			frame;
	size_t		frame_count;

	if (!init_fire_draw(game, ray, hit, &draw))
		return ;
	frame_count = game->rom->textures.fire->height
		/ game->rom->textures.fire->width;
	frame = (int)((game->ram->fire.animation.index + FIRE_FIRST_FRAME)
			% frame_count);
	draw_fire_pixels(game, x, &draw, frame);
}
