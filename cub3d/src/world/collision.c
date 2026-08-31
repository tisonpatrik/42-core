/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:30:31 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:30:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "game.h"
#include "fire.h"

bool	world_is_solid(const t_game *game, t_v2i map)
{
	t_tile	tile;

	tile = world_tile(game, map);
	if (tile == TILE_EMPTY)
		return (false);
	if (tile == TILE_FIRE && game->rom->bonus_enabled)
		return (fire_height_at(game, map) > 0.0);
	return (true);
}

bool	world_blocks_ray(const t_game *game, t_v2i map)
{
	t_tile	tile;

	tile = world_tile(game, map);
	if (tile == TILE_EMPTY)
		return (false);
	return (!(tile == TILE_FIRE && game->rom->bonus_enabled));
}
