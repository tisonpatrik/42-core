#include "world.h"
#include "game.h"

bool	world_contains(const t_game *game, t_v2i map)
{
	return (map.x >= 0 && map.y >= 0
		&& map.x < game->rom->map_size.x
		&& map.y < game->rom->map_size.y);
}

bool	world_index(const t_game *game, t_v2i map, size_t *index)
{
	if (!index || !world_contains(game, map))
		return (false);
	*index = (size_t)map.y * (size_t)game->rom->map_size.x
		+ (size_t)map.x;
	return (true);
}

size_t	world_cell_count(const t_game *game)
{
	return ((size_t)game->rom->map_size.x
		* (size_t)game->rom->map_size.y);
}

t_tile	world_tile(const t_game *game, t_v2i map)
{
	size_t	index;

	if (!world_index(game, map, &index))
		return (TILE_WALL);
	return ((t_tile)game->ram->tiles[index]);
}
