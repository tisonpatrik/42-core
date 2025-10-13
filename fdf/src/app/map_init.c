
# include "../../include/app.h"

void	malloc_grid(t_view *map)
{
	int	i;

	map->grid.grid3d = malloc(sizeof(t_point3d *) * map->grid_info.rows);
	map->grid.grid2d = malloc(sizeof(t_point2d *) * map->grid_info.rows);
	if (!(map->grid.grid2d) || !(map->grid.grid3d))
	{
		free_map(map);
		handle_error(MALLOC);
	}
	i = -1;
	while (++i < map->grid_info.rows)
	{
		map->grid.grid3d[i] = malloc(sizeof(t_point3d) * map->grid_info.cols);
		map->grid.grid2d[i] = malloc(sizeof(t_point2d) * map->grid_info.cols);
		if (!(map->grid.grid2d[i]) || !(map->grid.grid3d[i]))
		{
			if (i + 1 < map->grid_info.rows)
			{
				map->grid.grid3d[i + 1] = NULL;
				map->grid.grid2d[i + 1] = NULL;
			}
			free_map(map);
			handle_error(MALLOC);
		}
	}
}

void	init_map(t_view *map)
{
	// Initialize camera parameters
	map->camera.alpha = 0.46373398 / 2;
	map->camera.beta = 0.46373398;
	map->camera.xrotate = 0;
	map->camera.yrotate = 0;
	map->camera.zrotate = 0;
	map->camera.x_offset = WIDTH / 2;
	map->camera.y_offset = HEIGHT / 2;
	map->camera.zoom = 1;
	map->camera.zscale = 1;
	map->camera.interval = 0;
	
	// Initialize grid info
	map->grid_info.high = INT_MIN;
	map->grid_info.low = INT_MAX;
	map->grid_info.rows = 0;
	map->grid_info.cols = 0;
	
	// Initialize grid data
	map->grid.grid2d = NULL;
	map->grid.grid3d = NULL;
}

t_view	*parse_input(char *filename)
{
	int		fd;
	t_view	*map;

	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
		handle_error(FILE_ERROR);
	map = malloc(sizeof(t_view));
	if (!map)
	{
		close(fd);
		handle_error(MALLOC);
	}
	init_map(map);
	get_dimensions(fd, map);
	close(fd);
	malloc_grid(map);
	map->camera.interval = ft_min(WIDTH / map->grid_info.cols, HEIGHT / map->grid_info.rows) / 2.0;
	map->camera.interval = ft_max(2, map->camera.interval);
	fd = open(filename, O_RDONLY, 0777);
	parse_map(fd, map);
	close(fd);
	set_zcolor(map);
	return (map);
}
