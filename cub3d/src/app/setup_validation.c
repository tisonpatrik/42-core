#include <math.h>
#include "game.h"
#include "parsing.h"
#include "vec2.h"
#include "world.h"

#define CAMERA_DETERMINANT_EPSILON 0.000001

static bool	valid_paths(const t_wall_paths *paths)
{
	return (paths->north && paths->south && paths->west && paths->east);
}

static bool	valid_camera(const t_scene_config *config)
{
	double	determinant;

	if (!ft_v2d_is_finite(config->spawn_position)
		|| !ft_v2d_is_finite(config->spawn_direction)
		|| !ft_v2d_is_finite(config->camera_plane))
		return (false);
	determinant = ft_v2d_cross(config->spawn_direction,
			config->camera_plane);
	return (ft_v2d_length(config->spawn_direction) > 0.0
		&& ft_v2d_length(config->camera_plane) > 0.0
		&& fabs(determinant) > CAMERA_DETERMINANT_EPSILON);
}

static bool	valid_tile_value(uint8_t tile, bool bonus_enabled)
{
	if (tile == TILE_EMPTY || tile == TILE_WALL || tile == TILE_VOID)
		return (true);
	return (bonus_enabled && tile == TILE_FIRE);
}

static bool	valid_tiles(const t_scene_config *config, bool bonus_enabled)
{
	size_t	i;
	size_t	count;
	t_v2i	spawn;

	count = (size_t)config->map_size.x * (size_t)config->map_size.y;
	i = 0;
	while (i < count)
	{
		if (!valid_tile_value(config->tiles[i], bonus_enabled))
			return (false);
		i++;
	}
	spawn = world_cell(config->spawn_position);
	if (spawn.x < 0 || spawn.y < 0 || spawn.x >= config->map_size.x
		|| spawn.y >= config->map_size.y)
		return (false);
	return (config->tiles[(size_t)spawn.y * (size_t)config->map_size.x
			+ (size_t)spawn.x] == TILE_EMPTY);
}

bool	valid_scene_config(const t_scene_config *config, bool bonus_enabled)
{
	if (!config || config->map_size.x <= 0 || config->map_size.y <= 0
		|| !config->tiles || !valid_paths(&config->wall_paths))
		return (false);
	return (valid_camera(config) && valid_tiles(config, bonus_enabled));
}
