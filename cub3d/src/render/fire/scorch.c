/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scorch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:29:18 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:29:19 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "config.h"
#include "game.h"
#include "world.h"

static bool	scorch_texel(t_game *game, const t_rgba_view *source,
	t_v2d floor, t_v2i *texel)
{
	t_v2i			map;
	size_t			index;

	map = world_cell(floor);
	if (!world_contains(game, map))
		return (false);
	if (!world_index(game, map, &index))
		return (false);
	if (game->ram->tiles[index] != TILE_FIRE)
		return (false);
	texel->x = (int)((floor.x - map.x) * (double)source->width);
	texel->y = (int)((floor.y - map.y) * (double)source->height);
	return (true);
}

void	render_scorch_column(t_game *game, int x, t_ray *ray,
	const double *row_distances)
{
	t_rgba_view	destination;
	t_rgba_view	source;
	t_v2d		floor;
	t_v2i		texel;
	int			i;

	destination = image_rgba_view(game->frame_buffer);
	source = texture_rgba_view(game->rom->textures.scorch);
	i = 0;
	while (i < FLOOR_ROW_COUNT)
	{
		if (row_distances[i] < ray->wall.distance)
		{
			floor = ft_v2d_add(game->ram->player.pos,
					ft_v2d_scale(ray->dir, row_distances[i]));
			if (scorch_texel(game, &source, floor, &texel))
				ft_rgba_copy(ft_rgba_view_pixel(&destination, x,
						WINDOW_HEIGHT / 2 + 1 + i),
					ft_rgba_view_pixel(&source, texel.x, texel.y));
		}
		i++;
	}
}
