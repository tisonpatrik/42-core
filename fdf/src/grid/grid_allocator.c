/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_allocator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:33:44 by ptison            #+#    #+#             */
/*   Updated: 2025/10/14 00:11:40 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/app.h"

/* ========================================================================== */
/* GRID MEMORY ALLOCATION - Pure memory management                          */
/* ========================================================================== */

int	allocate_grid_memory(t_view *view)
{
	int	i;

	view->grid.grid3d = malloc(sizeof(t_point3d *) * view->grid.rows);
	if (!view->grid.grid3d)
		return (0);
	
	i = 0;
	while (i < view->grid.rows)
	{
		view->grid.grid3d[i] = malloc(sizeof(t_point3d) * view->grid.cols);
		if (!view->grid.grid3d[i])
		{
			/* Clean up already allocated rows */
			while (i > 0)
			{
				i--;
				free(view->grid.grid3d[i]);
			}
			free(view->grid.grid3d);
			view->grid.grid3d = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_grid_memory(t_view *view)
{
	int	i;

	if (!view || !view->grid.grid3d)
		return;
	
	i = 0;
	while (i < view->grid.rows)
	{
		free(view->grid.grid3d[i]);
		i++;
	}
	free(view->grid.grid3d);
	view->grid.grid3d = NULL;
}
