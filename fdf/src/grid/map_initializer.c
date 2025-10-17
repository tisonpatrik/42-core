/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_initializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:33:44 by ptison            #+#    #+#             */
/*   Updated: 2025/10/13 23:33:44 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/old_app.h"

/* ========================================================================== */
/* MAP INITIALIZATION - Pure initialization logic                           */
/* ========================================================================== */



void	get_grid_defaults(t_grid *grid)
{
	grid->high = INT_MIN;
	grid->low = INT_MAX;
	grid->rows = 0;
	grid->cols = 0;
	grid->grid3d = NULL;
}

void	init_map_defaults(t_view *view)
{
	init_camera_defaults(&view->camera, WIDTH, HEIGHT);
	get_grid_defaults(&view->grid);
}

void	calculate_camera_interval(t_view *view)
{
	double	interval;

	interval = ft_min(WIDTH / view->grid.cols, HEIGHT / view->grid.rows) / 2.0;
	view->camera.interval = ft_max(2, interval);
	
	printf("OLD IMPLEMENTATION - Interval calculated:\n");
	printf("  Grid: %dx%d\n", view->grid.rows, view->grid.cols);
	printf("  Calculated interval: %.2f\n", view->camera.interval);
}
