#include "fire.h"
#include "game.h"
#include "world.h"

void	fire_init(t_game *game)
{
	size_t			i;
	size_t			tile_count;
	t_fire_cell		*cell;

	tile_count = world_cell_count(game);
	i = 0;
	while (i < tile_count)
	{
		cell = &game->ram->fire.cells[i];
		if (game->ram->tiles[i] == TILE_FIRE)
		{
			cell->state = FIRE_IDLE;
			cell->height = 1.0;
			game->ram->fire.count++;
		}
		i++;
	}
}

static void	fire_update_animation(t_game *game, double delta_time)
{
	t_fire_system	*fire;
	size_t			frame_count;

	fire = &game->ram->fire;
	frame_count = game->rom->textures.fire->height
		/ game->rom->textures.fire->width;
	ft_step_cycle_advance(&fire->animation, delta_time,
		FIRE_ANIMATION_INTERVAL, frame_count);
}

void	fire_update(t_game *game, double delta_time)
{
	if (game->ram->fire.count == 0)
		return ;
	fire_update_animation(game, delta_time);
	fire_update_cells(game, delta_time);
}

double	fire_height_at(const t_game *game, t_v2i map)
{
	size_t	index;

	if (world_tile(game, map) != TILE_FIRE
		|| !world_index(game, map, &index))
		return (0.0);
	return (game->ram->fire.cells[index].height);
}
