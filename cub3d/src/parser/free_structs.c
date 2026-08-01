#include "parsing.h"

static void	set_ptr_null(void **ptr)
{
	if (!ptr || !*ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

void	free_scene_cfg(t_scene_config *cfg)
{
	if (!cfg)
		return ;
	set_ptr_null((void **)&cfg->wall_paths.north);
	set_ptr_null((void **)&cfg->wall_paths.south);
	set_ptr_null((void **)&cfg->wall_paths.west);
	set_ptr_null((void **)&cfg->wall_paths.east);
	set_ptr_null((void **)&cfg->tiles);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->rows)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	free_file(t_file *file)
{
	int	i;

	if (!file)
		return ;
	i = 0;
	if (file->lines)
	{
		while (i < file->line_count)
		{
			if (file->lines[i])
				free(file->lines[i]);
			i++;
		}
		free(file->lines);
	}
	if (file->map.grid)
		free_map(&file->map);
}
