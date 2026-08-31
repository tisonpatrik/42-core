/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:28:40 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:28:41 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "orb.h"
#include "allocator.h"
#include "game.h"
#include "mem.h"
#include "vec2.h"
#include "world.h"

#define NEIGHBOR_LEFT 0
#define NEIGHBOR_RIGHT 1
#define NEIGHBOR_UP 2
#define NEIGHBOR_DOWN 3
#define NEIGHBOR_COUNT 4

static bool	mark_candidate(t_game *game, uint8_t *visited, t_v2i map)
{
	size_t	index;
	t_tile	tile;

	if (!world_contains(game, map))
		return (false);
	tile = world_tile(game, map);
	if (tile != TILE_EMPTY && tile != TILE_FIRE)
		return (false);
	if (!world_index(game, map, &index))
		return (false);
	if (visited[index])
		return (false);
	visited[index] = 1;
	return (true);
}

static t_v2i	adjacent_cell(t_v2i cell, int neighbor)
{
	if (neighbor == NEIGHBOR_LEFT)
		cell.x--;
	else if (neighbor == NEIGHBOR_RIGHT)
		cell.x++;
	else if (neighbor == NEIGHBOR_UP)
		cell.y--;
	else if (neighbor == NEIGHBOR_DOWN)
		cell.y++;
	return (cell);
}

static size_t	flood_reachable(t_game *game, uint8_t *visited, t_v2i *queue)
{
	t_v2i	candidate;
	size_t	head;
	size_t	tail;
	size_t	index;
	int		neighbor;

	queue[0] = world_cell(game->ram->player.pos);
	if (!world_index(game, queue[0], &index))
		return (0);
	visited[index] = 1;
	head = 0;
	tail = 1;
	while (head < tail)
	{
		neighbor = NEIGHBOR_LEFT;
		while (neighbor < NEIGHBOR_COUNT)
		{
			candidate = adjacent_cell(queue[head], neighbor);
			if (mark_candidate(game, visited, candidate))
				queue[tail++] = candidate;
			neighbor++;
		}
		head++;
	}
	return (tail);
}

static size_t	compact_candidates(t_game *game, t_v2i *cells, size_t count)
{
	t_v2i	spawn;
	size_t	read_index;
	size_t	write_index;

	spawn = world_cell(game->ram->player.pos);
	read_index = 0;
	write_index = 0;
	while (read_index < count)
	{
		if (world_tile(game, cells[read_index]) == TILE_EMPTY
			&& !ft_v2i_equal(spawn, cells[read_index]))
			cells[write_index++] = cells[read_index];
		read_index++;
	}
	return (write_index);
}

/* Scratch memory disappears after reachable empty cells have been sampled. */
bool	orb_generate(t_game *game, uint32_t seed)
{
	t_arena_temp	scratch;
	uint8_t			*visited;
	t_v2i			*candidates;
	size_t			tile_count;
	size_t			candidate_count;

	ft_bzero(&game->ram->orbs, sizeof(game->ram->orbs));
	tile_count = world_cell_count(game);
	scratch = ft_scratch_begin(game->arena);
	visited = ft_arena_push_array(game->arena, tile_count, sizeof(uint8_t));
	candidates = ft_arena_push_array(game->arena, tile_count, sizeof(t_v2i));
	if (!visited || !candidates)
		return (ft_scratch_end(scratch), false);
	candidate_count = flood_reachable(game, visited, candidates);
	candidate_count = compact_candidates(game, candidates, candidate_count);
	orb_select_positions(game, candidates, candidate_count, seed);
	ft_scratch_end(scratch);
	return (true);
}
