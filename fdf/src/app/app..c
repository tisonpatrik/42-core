/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app..c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:47:59 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 10:43:10 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/app.h"

static void	draw_image_hook_app(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	render_image(app->renderer.img, app->grid);
}

t_app	*init_app(char *filename)
{
	t_app	*app;

	app = malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->renderer = init_renderer();
	app->grid = create_grid_from_file(filename, WIDTH, HEIGHT);
	if (!app->grid)
	{
		free(app);
		return (NULL);
	}
	app->camera = init_camera_defaults();
	return (app);
}

void	free_app(t_app *app)
{
	if (!app)
		return ;
	if (app->grid)
		free_grid(app->grid);
	if (app->renderer.mlx)
		mlx_terminate(app->renderer.mlx);
	free(app);
}

void	run_app(t_app *app)
{
	display_menu(app->renderer.mlx);
	render_image(app->renderer.img, app->grid);
	if (mlx_image_to_window(app->renderer.mlx, app->renderer.img, 0, 0) == -1)
	{
		mlx_close_window(app->renderer.mlx);
		free_grid(app->grid);
		free(app);
		fdf_error(mlx_strerror(mlx_errno));
	}
	mlx_loop_hook(app->renderer.mlx, &hook, app);
	mlx_loop_hook(app->renderer.mlx, &draw_image_hook_app, app);
	mlx_loop(app->renderer.mlx);
}
