/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app..c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:47:59 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 00:20:53 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../include/app.h"

t_app	*init_app(char *filename)
{
    t_heightmap *heightmap = read_heightmap_from_file(filename);
	t_camera camera;
	t_grid *grid;
	t_app *app;
	
	grid = get_grid(heightmap);
	
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
	app->cam = camera;
	app->r.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	app->r.img = mlx_new_image(app->r.mlx, WIDTH, HEIGHT);
	app->r.width = WIDTH;
	app->r.height = HEIGHT;

	return (app);
}

static void	draw_image_hook_app(void *param)
{
	t_app	*app = (t_app *)param;
	draw_image(app->r.img, app->grid, &app->cam);
}

void	free_app(t_app *app)
{
	if (!app)
		return;
	if (app->grid)
		free_grid(app->grid);
	if (app->r.mlx)
		mlx_terminate(app->r.mlx);
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
	display_menu(app->r.mlx);
	draw_image(app->r.img, app->grid, &app->cam);
	if (mlx_image_to_window(app->r.mlx, app->r.img, 0, 0) == -1)
	{
		mlx_close_window(app->r.mlx);
		free_grid(app->grid);
		free(app);
		handle_error(mlx_strerror(mlx_errno));
	}
	mlx_loop_hook(app->r.mlx, &hook, app);
	mlx_loop_hook(app->r.mlx, &hook_rotate, app);
	mlx_loop_hook(app->r.mlx, &hook_project, app);
	mlx_scroll_hook(app->r.mlx, &scrollhook, app);
	mlx_loop_hook(app->r.mlx, &draw_image_hook_app, app);
	mlx_loop(app->r.mlx);
}