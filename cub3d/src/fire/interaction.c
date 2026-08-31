/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:28:30 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:28:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fire.h"
#include "game.h"
#include "world.h"

static bool	player_is_at(t_game *game, t_v2i map)
{
	t_v2i	player_map;

	player_map = world_cell(game->ram->player.pos);
	return (ft_v2i_equal(player_map, map));
}

void	fire_toggle(t_game *game, t_v2i map)
{
	t_fire_cell	*cell;
	size_t		index;

	if (world_tile(game, map) != TILE_FIRE
		|| !world_index(game, map, &index))
		return ;
	cell = &game->ram->fire.cells[index];
	if (cell->state == FIRE_IDLE)
	{
		cell->state = FIRE_SHRINKING;
		return ;
	}
	if (cell->state == FIRE_HIDDEN && !player_is_at(game, map))
		cell->state = FIRE_GROWING;
}
