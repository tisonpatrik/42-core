#include "parsing.h"
#include "world.h"

static	int	convert_player_camera(t_map *map, t_scene_config *cfg)
{
	if (map->p_dir == 'N')
	{
		cfg->camera_plane.y = 0.0;
		cfg->camera_plane.x = 0.66;
	}
	else if (map->p_dir == 'S')
	{
		cfg->camera_plane.y = 0.0;
		cfg->camera_plane.x = -0.66;
	}
	else if (map->p_dir == 'E')
	{
		cfg->camera_plane.y = 0.66;
		cfg->camera_plane.x = 0.00;
	}
	else if (map->p_dir == 'W')
	{
		cfg->camera_plane.y = -0.66;
		cfg->camera_plane.x = 0.00;
	}
	else
		return (-1);
	return (0);
}

static int	convert_player_dir(t_map *map, t_scene_config *cfg)
{
	if (map->p_dir == 'N')
	{
		cfg->spawn_direction.y = -1.0;
		cfg->spawn_direction.x = 0.0;
	}
	else if (map->p_dir == 'S')
	{
		cfg->spawn_direction.y = 1.0;
		cfg->spawn_direction.x = 0.0;
	}
	else if (map->p_dir == 'E')
	{
		cfg->spawn_direction.y = 0.0;
		cfg->spawn_direction.x = 1.0;
	}
	else if (map->p_dir == 'W')
	{
		cfg->spawn_direction.y = 0.0;
		cfg->spawn_direction.x = -1.0;
	}
	else
		return (-1);
	return (0);
}

static uint8_t	*convert_grid(t_map *map)
{
	uint8_t	*raw;
	int		y;
	int		x;
	int		index;

	raw = malloc(sizeof(uint8_t) * (map->rows * map->max_cols));
	if (!raw)
		return (NULL);
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->max_cols)
		{
			index = (y * map->max_cols) + x;
			if (map->grid[y][x] == '1')
				raw[index] = TILE_WALL;
			else if (map->grid[y][x] == '2')
				raw[index] = TILE_FIRE;
			else if (map->grid[y][x] == ' ')
				raw[index] = TILE_VOID;
			else
				raw[index] = TILE_EMPTY;
			x++;
		}
		y++;
	}
	return (raw);
}

int	fill_rest_cfg(t_map *map, t_scene_config *cfg)
{
	cfg->map_size = (t_v2i){map->max_cols, map->rows};
	cfg->tiles = convert_grid(map);
	if (!cfg->tiles)
		return (display_error("Map conversion to ui8_t failed!"), -1);
	cfg->spawn_position.y = (double)map->p_y + 0.5;
	cfg->spawn_position.x = (double)map->p_x + 0.5;
	if (convert_player_dir(map, cfg) == -1)
		return (display_error("Player dir conversion failed!"), -1);
	if (convert_player_camera(map, cfg) == -1)
		return (display_error("Camera conversion failed!"), -1);
	return (0);
}
