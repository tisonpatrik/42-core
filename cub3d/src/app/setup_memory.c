#include <stdint.h>
#include <stdlib.h>
#include "allocator.h"
#include "config.h"
#include "game.h"
#include "mem.h"
#include "parsing.h"

static size_t	tile_count(const t_scene_config *config)
{
	return ((size_t)config->map_size.x * (size_t)config->map_size.y);
}

static bool	add_bonus_memory(size_t *total, size_t tiles)
{
	return (ft_arena_measure(total, WINDOW_WIDTH, sizeof(double))
		&& ft_arena_measure(total, tiles, sizeof(uint8_t))
		&& ft_arena_measure(total, tiles, sizeof(t_v2i)));
}

bool	game_memory_size(const t_scene_config *config, bool bonus_enabled,
	size_t *total)
{
	size_t	tiles;
	size_t	hits;

	if (!config || !total || config->map_size.x <= 0
		|| config->map_size.y <= 0)
		return (false);
	if ((size_t)config->map_size.x > SIZE_MAX
		/ (size_t)config->map_size.y)
		return (false);
	tiles = tile_count(config);
	hits = (size_t)config->map_size.x + (size_t)config->map_size.y;
	*total = 0;
	if (!(ft_arena_measure(total, 1, sizeof(t_rom))
			&& ft_arena_measure(total, 1, sizeof(t_ram))
			&& ft_arena_measure(total, tiles, sizeof(uint8_t))
			&& ft_arena_measure(total, tiles, sizeof(t_fire_cell))
			&& ft_arena_measure(total, hits, sizeof(t_ray_hit))))
		return (false);
	return (!bonus_enabled || add_bonus_memory(total, tiles));
}

int	setup_ram(t_game *game, const t_scene_config *config,
	bool bonus_enabled)
{
	size_t	tiles;
	size_t	hits;
	t_ram	*ram;

	tiles = tile_count(config);
	hits = (size_t)config->map_size.x + (size_t)config->map_size.y;
	game->ram = ft_arena_push(game->arena, sizeof(t_ram));
	if (!game->ram)
		return (EXIT_FAILURE);
	ram = game->ram;
	ram->tiles = ft_arena_push_array(game->arena, tiles, sizeof(uint8_t));
	ram->fire.cells = ft_arena_push_array(game->arena,
			tiles, sizeof(t_fire_cell));
	ram->fire_hits.items = ft_arena_push_array(game->arena,
			hits, sizeof(t_ray_hit));
	if (bonus_enabled)
		ram->sprite_depth = ft_arena_push_array(game->arena,
				WINDOW_WIDTH, sizeof(double));
	if (!ram->tiles || !ram->fire.cells || !ram->fire_hits.items)
		return (EXIT_FAILURE);
	if (bonus_enabled && !ram->sprite_depth)
		return (EXIT_FAILURE);
	ram->fire_hits.capacity = hits;
	ft_memcpy(ram->tiles, config->tiles, tiles * sizeof(uint8_t));
	return (EXIT_SUCCESS);
}
