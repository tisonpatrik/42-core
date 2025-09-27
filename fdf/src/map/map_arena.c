/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:43:16 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 16:43:12 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"

void	free_map_arena(t_map *map)
{
	if (!map)
		return ;
	if (map->arena)
		ft_arena_destroy(map->arena);
	// Don't free map itself - it's not allocated with malloc
}

size_t	calculate_arena_size(int nrows, int total_cells)
{
	size_t	size;
	size_t	cells_size;
	size_t	row_counts_size;
	size_t	row_offsets_size;

	cells_size = sizeof(t_cell) * (size_t)total_cells;
	row_counts_size = sizeof(int) * (size_t)nrows;
	row_offsets_size = sizeof(int) * (size_t)(nrows + 1);
	
	// Apply 8-byte alignment (same as ft_arena_alloc)
	cells_size = (cells_size + 7) & ~7;
	row_counts_size = (row_counts_size + 7) & ~7;
	row_offsets_size = (row_offsets_size + 7) & ~7;
	
	size = cells_size + row_counts_size + row_offsets_size;
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
