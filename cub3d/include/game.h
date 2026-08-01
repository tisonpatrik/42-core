#ifndef GAME_H
# define GAME_H

# include <stdbool.h>
# include <stddef.h>
# include "MLX42.h"
# include "allocator.h"
# include "ram.h"
# include "rom.h"

struct	s_scene_config;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*frame_buffer;
	t_arena			*arena;
	t_rom			*rom;
	t_ram			*ram;
}	t_game;

int		game_setup(t_game *game, const struct s_scene_config *config);
void	game_cleanup(t_game *game);
int		run_engine(t_game *game);
void	engine_shutdown(t_game *game);
bool	valid_scene_config(const struct s_scene_config *config,
			bool bonus_enabled);
bool	game_memory_size(const struct s_scene_config *config,
			bool bonus_enabled, size_t *total);
int		setup_ram(t_game *game, const struct s_scene_config *config,
			bool bonus_enabled);

#endif
