/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:37:26 by ptison            #+#    #+#             */
/*   Updated: 2025/10/11 17:55:16 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/app.h"

static t_map  *init_map(const char *file_name)
{
	t_map	*map = read_map_from_file(file_name);
	if (!map)
	{
		ft_putstr_fd("Error: Failed to read map file\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (map);
}

static mlx_t *init_mlx(t_map *map)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	
	// Use reasonable initial size - MLX will resize to maximized
	mlx_t	*mlx = mlx_init(1920, 1080, "FDF", true);
	if (!mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MLX\n", STDERR_FILENO);
		t_app temp_app = {NULL, map, NULL};
		free_app(temp_app);
		exit(EXIT_FAILURE);
	}
	return (mlx);
}

static mlx_image_t *init_image(mlx_t *mlx, t_map *map)
{
	mlx_image_t	*image = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!image)
	{
		ft_putstr_fd("Error: Failed to create image\n", STDERR_FILENO);
		t_app temp_app = {mlx, map, NULL};
		free_app(temp_app);
		exit(EXIT_FAILURE);
	}
	return (image);
}


t_app	app_init(const char *file_name)
{
	t_app	app;
	t_map	*map;
	mlx_image_t	*image;
	mlx_t	*mlx;

    map = init_map(file_name);
	mlx = init_mlx(map);
	image = init_image(mlx, map);

	
	app.mlx = mlx;
	app.map = map;
	app.image = image;
	
	// Render the initial map once
	render_map(&app);
	
	return (app);
}

void	free_app(t_app app)
{
    if (app.map)
	    free_map(app.map);
	
	if (app.image)
		mlx_delete_image(app.mlx, app.image);
	
	if (app.mlx)
		mlx_terminate(app.mlx);
    
}