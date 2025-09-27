/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:43:16 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 12:47:54 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"

void	free_map_arena(t_map *map)
{
	if (!map)
		return ;
	if (map->arena)
		ft_arena_destroy(map->arena);
	free(map);
}

size_t	calculate_arena_size(int nrows, int total_cells)
{
	size_t	size;

	size = 0;
	size += sizeof(t_cell) * (size_t)total_cells;
	size += sizeof(int) * (size_t)nrows;
	size += sizeof(int) * (size_t)(nrows + 1);
	return (size);
}

int	setup_arena_layout(t_map *map, int nrows, int total_cells)
{
	map->cells = (t_cell *)ft_arena_alloc(map->arena, sizeof(t_cell)
			* (size_t)total_cells);
	map->row_counts = (int *)ft_arena_alloc(map->arena, sizeof(int)
			* (size_t)nrows);
	map->row_offsets = (int *)ft_arena_alloc(map->arena, sizeof(int)
			* (size_t)(nrows + 1));
	return (map->cells && map->row_counts && map->row_offsets);
}
