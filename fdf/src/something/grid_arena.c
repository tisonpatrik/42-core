/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:00:34 by ptison            #+#    #+#             */
/*   Updated: 2025/10/16 11:16:02 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/something.h"

t_grid	*allocate_grid(int rows, int cols)
{
	t_arena	*arena;
	t_grid	*grid;
	size_t	total_size;
	int		i;

	// Calculate total memory needed
	total_size = sizeof(t_grid) + 
	             sizeof(t_point3d *) * rows + 
	             sizeof(t_point3d) * rows * cols;
	
	arena = ft_arena_create(total_size);
	if (!arena)
		return (NULL);
	
	// Allocate grid structure
	grid = ft_arena_alloc(arena, sizeof(t_grid));
	if (!grid)
	{
		ft_arena_destroy(arena);
		return (NULL);
	}
	
	// Allocate array of pointers to rows
	grid->grid3d = ft_arena_alloc(arena, sizeof(t_point3d *) * rows);
	if (!grid->grid3d)
	{
		ft_arena_destroy(arena);
		return (NULL);
	}
	
	// Allocate each row
	i = 0;
	while (i < rows)
	{
		grid->grid3d[i] = ft_arena_alloc(arena, sizeof(t_point3d) * cols);
		if (!grid->grid3d[i])
		{
			ft_arena_destroy(arena);
			return (NULL);
		}
		i++;
	}
	
	// Initialize grid fields
	grid->rows = rows;
	grid->cols = cols;
	grid->high = INT_MIN;
	grid->low = INT_MAX;
	grid->arena = arena;
	
	return (grid);
}

void	free_grid(t_view *view)
{
	if (!view || !view->grid.arena)
		return;
	
	ft_arena_destroy(view->grid.arena);
	view->grid.arena = NULL;
	view->grid.grid3d = NULL;
}
