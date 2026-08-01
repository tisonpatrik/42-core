#include "game.h"
#include "allocator.h"
#include "mem.h"

void	engine_shutdown(t_game *game)
{
	if (game->mlx)
		mlx_terminate(game->mlx);
	game->mlx = NULL;
	game->frame_buffer = NULL;
}

void	game_cleanup(t_game *game)
{
	if (!game)
		return ;
	if (game->rom)
		textures_cleanup(&game->rom->textures);
	if (game->arena)
		ft_arena_destroy(game->arena);
	ft_bzero(game, sizeof(*game));
}
