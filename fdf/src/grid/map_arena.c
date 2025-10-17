/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:43:16 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 00:33:14 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/grid.h"

void	free_heightmap(t_heightmap *heightmap)
{
	if (!heightmap)
		return ;
	if (heightmap->arena)
		ft_arena_destroy(heightmap->arena);
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

int	setup_arena_layout(t_heightmap *heightmap, int nrows, int ncols)
{
	int	total_cells;

	total_cells = nrows * ncols;
	heightmap->points = (t_point *)ft_arena_alloc(heightmap->arena, sizeof(t_point)
			* (size_t)total_cells);
	return (heightmap->points != NULL);
}

t_heightmap	*allocate_heightmap(t_heightmap_info *info)
{
	t_heightmap	*heightmap;
	size_t	arena_size;

	heightmap = malloc(sizeof(t_heightmap));
	if (!heightmap)
		return (NULL);
	arena_size = calculate_arena_size(info->expected_count_rows, info->expected_count_columns);
	heightmap->arena = ft_arena_create(arena_size);
	if (!heightmap->arena)
	{
		free(heightmap);
		return (NULL);
	}
	heightmap->rows = info->expected_count_rows;
	heightmap->cols = info->expected_count_columns;
	if (!setup_arena_layout(heightmap, heightmap->rows, heightmap->cols))
	{
		ft_arena_destroy(heightmap->arena);
		free(heightmap);
		return (NULL);
	}
	return (heightmap);
}
