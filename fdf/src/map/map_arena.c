/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:43:16 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 17:34:22 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->arena)
		ft_arena_destroy(map->arena);
}

size_t	calculate_arena_size(int nrows, int ncols)
{
	size_t	size;
	size_t	cells_size;
	int		total_cells;

	total_cells = nrows * ncols;
	cells_size = sizeof(t_cell) * (size_t)total_cells;
	cells_size = (cells_size + 7) & ~7;
	size = cells_size;
	return (size);
}

int	setup_arena_layout(t_map *map, int nrows, int ncols)
{
	int	total_cells;

	total_cells = nrows * ncols;
	map->cells = (t_cell *)ft_arena_alloc(map->arena, sizeof(t_cell)
			* (size_t)total_cells);
	return (map->cells != NULL);
}

t_map	*map_arena_init(t_map_info *info)
{
	t_map	*map;
	size_t	arena_size;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	arena_size = calculate_arena_size(info->nrows, info->ncols);
	map->arena = ft_arena_create(arena_size);
	if (!map->arena)
	{
		free(map);
		return (NULL);
	}
	map->nrows = info->nrows;
	map->ncols = info->ncols;
	map->total_cells = info->total_cells;
	if (!setup_arena_layout(map, map->nrows, map->ncols))
	{
		ft_arena_destroy(map->arena);
		free(map);
		return (NULL);
	}
	return (map);
}
