/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:00:34 by ptison            #+#    #+#             */
/*   Updated: 2025/10/19 21:07:33 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/grid.h"

static t_arena	*create_grid_arena(int rows, int cols)
{
	size_t	total_size;

	total_size = sizeof(t_grid) + sizeof(t_point3d *) * rows + sizeof(t_point3d)
		* rows * cols;
	return (ft_arena_create(total_size));
}

static t_grid	*allocate_grid_structure(t_arena *arena, int rows)
{
	t_grid	*grid;

	grid = ft_arena_alloc(arena, sizeof(t_grid));
	if (!grid)
		return (NULL);
	grid->grid3d = ft_arena_alloc(arena, sizeof(t_point3d *) * rows);
	if (!grid->grid3d)
		return (NULL);
	return (grid);
}

static bool	allocate_grid_rows(t_grid *grid, t_arena *arena, int rows, int cols)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		grid->grid3d[i] = ft_arena_alloc(arena, sizeof(t_point3d) * cols);
		if (!grid->grid3d[i])
			return (false);
		i++;
	}
	return (true);
}

t_grid	*allocate_grid(int rows, int cols)
{
	t_arena	*arena;
	t_grid	*grid;

	arena = create_grid_arena(rows, cols);
	if (!arena)
		return (NULL);
	grid = allocate_grid_structure(arena, rows);
	if (!grid)
	{
		ft_arena_destroy(arena);
		return (NULL);
	}
	if (!allocate_grid_rows(grid, arena, rows, cols))
	{
		ft_arena_destroy(arena);
		return (NULL);
	}
	grid->rows = rows;
	grid->cols = cols;
	grid->high = INT_MIN;
	grid->low = INT_MAX;
	grid->arena = arena;
	return (grid);
}

void	free_grid(t_grid *grid)
{
	if (!grid || !grid->arena)
		return ;
	ft_arena_destroy(grid->arena);
}
