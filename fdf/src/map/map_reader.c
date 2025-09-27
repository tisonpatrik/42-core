/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:45:10 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 16:45:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/map.h"

// ============================================================================
// MAP READER - Main orchestrator function
// ============================================================================

t_map	*read_map_from_file(const char *file_name)
{
	t_map		*map;
	t_map_info	*info;
	size_t		arena_size;

	// Step 1: Analyze file structure
	info = analyze_map_file(file_name);
	if (!info)
		return (NULL);
	
	// Step 2: Allocate map structure
	map = malloc(sizeof(t_map));
	if (!map)
	{
		free_map_info(info);
		return (NULL);
	}
	
	// Step 3: Setup memory arena
	arena_size = calculate_arena_size(info->nrows, info->total_cells);
	map->arena = ft_arena_create(arena_size);
	if (!map->arena)
	{
		free(map);
		free_map_info(info);
		return (NULL);
	}
	
	// Step 4: Setup arena layout
	map->nrows = info->nrows;
	map->total_cells = info->total_cells;
	
	if (!setup_arena_layout(map, map->nrows, map->total_cells))
	{
		ft_arena_destroy(map->arena);
		free(map);
		free_map_info(info);
		return (NULL);
	}
	
	// Step 5: Copy row_counts from map_info to arena
	for (int i = 0; i < map->nrows; i++)
		map->row_counts[i] = info->row_counts[i];
	
	// Step 6: Calculate row_offsets
	map->row_offsets[0] = 0;
	for (int i = 1; i <= map->nrows; i++)
		map->row_offsets[i] = map->row_offsets[i-1] + map->row_counts[i-1];
	
	// Step 7: Parse actual data
	if (!parse_map_data(map, file_name))
	{
		ft_arena_destroy(map->arena);
		free(map);
		free_map_info(info);
		return (NULL);
	}
	
	// Step 8: Cleanup map_info
	free_map_info(info);
	
	return (map);
}

// ============================================================================
// MAP CLEANUP
// ============================================================================

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->arena)
		ft_arena_destroy(map->arena);
	free(map);
}
