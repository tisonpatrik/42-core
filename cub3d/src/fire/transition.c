/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:28:33 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:28:34 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fire.h"
#include "game.h"
#include "world.h"

static void	shrink_cell(t_fire_cell *cell, double change)
{
	cell->height -= change;
	if (cell->height <= 0.0)
	{
		cell->height = 0.0;
		cell->state = FIRE_HIDDEN;
	}
}

static void	grow_cell(t_fire_cell *cell, double change)
{
	cell->height += change;
	if (cell->height >= 1.0)
	{
		cell->height = 1.0;
		cell->state = FIRE_IDLE;
	}
}

static void	update_cell(t_fire_cell *cell, double delta_time)
{
	double	change;

	change = delta_time * FIRE_TRANSITION_SPEED;
	if (cell->state == FIRE_SHRINKING)
		shrink_cell(cell, change);
	if (cell->state == FIRE_GROWING)
		grow_cell(cell, change);
}

void	fire_update_cells(t_game *game, double delta_time)
{
	size_t	i;
	size_t	tile_count;

	tile_count = world_cell_count(game);
	i = 0;
	while (i < tile_count)
	{
		if (game->ram->tiles[i] == TILE_FIRE)
			update_cell(&game->ram->fire.cells[i], delta_time);
		i++;
	}
}
