#ifndef WORLD_H
# define WORLD_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include "vec2.h"

struct	s_game;

typedef enum e_tile
{
	TILE_EMPTY,
	TILE_WALL,
	TILE_FIRE,
	TILE_VOID
}	t_tile;

/* All coordinate and tile access is centralized here for bounds safety. */
bool		world_contains(const struct s_game *game, t_v2i map);
bool		world_index(const struct s_game *game, t_v2i map, size_t *index);
size_t		world_cell_count(const struct s_game *game);
t_tile		world_tile(const struct s_game *game, t_v2i map);
bool		world_is_solid(const struct s_game *game, t_v2i map);
bool		world_blocks_ray(const struct s_game *game, t_v2i map);
t_v2i		world_cell(t_v2d position);
t_v2d		world_cell_center(t_v2i map);

#endif
