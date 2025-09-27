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

void	map_init(t_map *map)
{
	map->rows = NULL;
	map->cols = NULL;
	map->nrows = 0;
	map->cap = 0;
}

void	map_free(t_map *map)
{
	if (!map)
		return ;
	for (int r = 0; r < map->nrows; r++)
		free(map->rows[r]);
	free(map->rows);
	free(map->cols);
	map->rows = NULL;
	map->cols = NULL;
	map->nrows = map->cap = 0;
}

static void	map_grow_if_needed(t_map *map)
{
	int		new_cap;
	t_cell	**new_rows;
	int		*new_cols;

	if (map->nrows < map->cap)
		return ;
	if (map->cap == 0)
		new_cap = 8;
	else
		new_cap = map->cap * 2;
	new_rows = (t_cell **)realloc(map->rows, sizeof(t_cell *) * new_cap);
	new_cols = (int *)realloc(map->cols, sizeof(int) * new_cap);
	if (!new_rows || !new_cols)
	{
		map_free(map);
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	map->rows = new_rows;
	map->cols = new_cols;
	map->cap = new_cap;
}

void	map_push_row(t_map *map, t_cell *line_cells, int len)
{
	map_grow_if_needed(map);
	map->rows[map->nrows] = line_cells;
	map->cols[map->nrows] = len;
	map->nrows++;
}
