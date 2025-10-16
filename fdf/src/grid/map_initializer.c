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

# include "../../include/app.h"

/* ========================================================================== */
/* MAP INITIALIZATION - Pure initialization logic                           */
/* ========================================================================== */

void	init_camera_defaults(t_camera *camera)
{
	camera->alpha = 0.46373398 / 2;
	camera->beta = 0.46373398;
	camera->xrotate = 0;
	camera->yrotate = 0;
	camera->zrotate = 0;
	camera->x_offset = WIDTH / 2;
	camera->y_offset = HEIGHT / 2;
	camera->zoom = 1;
	camera->zscale = 1;
	camera->interval = 0;
}

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
	init_camera_defaults(&view->camera);
	get_grid_defaults(&view->grid);
}

void	calculate_camera_interval(t_view *view)
{
	double	interval;

	interval = ft_min(WIDTH / view->grid.cols, HEIGHT / view->grid.rows) / 2.0;
	view->camera.interval = ft_max(2, interval);
}
