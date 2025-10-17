/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app..c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:47:59 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 00:32:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../include/app.h"

t_app	*init_app(char *filename)
{
    
	t_camera camera;
	t_grid *grid;
	t_app *app;
	
	grid = get_grid(filename, WIDTH, HEIGHT);
	
	if (!grid)
		return (NULL);

	init_camera_defaults(&camera, WIDTH, HEIGHT);

	app = malloc(sizeof(t_app));
	if (!app)
	{
		free_grid(grid);
		return (NULL);
	}

	app->grid = grid;  // Use pointer instead of copy
	app->camera = camera;
	app->renderer.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	app->renderer.img = mlx_new_image(app->renderer.mlx, WIDTH, HEIGHT);
	app->renderer.width = WIDTH;
	app->renderer.height = HEIGHT;

	return (app);
}

static void	draw_image_hook_app(void *param)
{
	t_app	*app = (t_app *)param;
	draw_image(app->renderer.img, app->grid, &app->camera);
}

void	free_app(t_app *app)
{
	if (!app)
		return;
	if (app->grid)
		free_grid(app->grid);
	if (app->renderer.mlx)
		mlx_terminate(app->renderer.mlx);
	free(app);
}


static void	handle_error(const char *message)
{
	if (errno == 0)
	{
		ft_putstr_fd("FdF: ", 2);
		ft_putendl_fd((char *)message, 2);
	}
	else
		perror("FdF");
	exit(1);
}
void	run_app(t_app *app)
{
	display_menu(app->renderer.mlx);
	draw_image(app->renderer.img, app->grid, &app->camera);
	if (mlx_image_to_window(app->renderer.mlx, app->renderer.img, 0, 0) == -1)
	{
		mlx_close_window(app->renderer.mlx);
		free_grid(app->grid);
		free(app);
		handle_error(mlx_strerror(mlx_errno));
	}
	mlx_loop_hook(app->renderer.mlx, &hook, app);
	mlx_loop_hook(app->renderer.mlx, &hook_rotate, app);
	mlx_loop_hook(app->renderer.mlx, &hook_project, app);
	mlx_scroll_hook(app->renderer.mlx, &scrollhook, app);
	mlx_loop_hook(app->renderer.mlx, &draw_image_hook_app, app);
	mlx_loop(app->renderer.mlx);
}