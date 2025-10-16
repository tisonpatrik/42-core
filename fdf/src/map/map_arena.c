/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:43:16 by ptison            #+#    #+#             */
/*   Updated: 2025/10/15 15:03:37 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/map.h"

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
	cells_size = sizeof(t_point) * (size_t)total_cells;
	cells_size = (cells_size + 7) & ~7;
	size = cells_size;
	return (size);
}

int	setup_arena_layout(t_map *map, int nrows, int ncols)
{
	int	total_cells;

	total_cells = nrows * ncols;
	map->points = (t_point *)ft_arena_alloc(map->arena, sizeof(t_point)
			* (size_t)total_cells);
	return (map->points != NULL);
}

t_map	*alocate_map(t_map_info *info)
{
	t_map	*map;
	size_t	arena_size;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	arena_size = calculate_arena_size(info->expected_count_rows, info->expected_count_columns);
	map->arena = ft_arena_create(arena_size);
	if (!map->arena)
	{
		free(map);
		return (NULL);
	}
	map->rows = info->expected_count_rows;
	map->cols = info->expected_count_columns;
	if (!setup_arena_layout(map, map->rows, map->cols))
	{
		ft_arena_destroy(map->arena);
		free(map);
		return (NULL);
	}
	return (map);
}
