#include "input.h"
#include "game.h"
#include "ram.h"
#include "fire.h"
#include "vec2.h"
#include "world.h"

#define INTERACTION_REACH 1.0

static t_v2i	action_target(t_player *player)
{
	t_v2d	point;

	point = ft_v2d_add(player->pos,
			ft_v2d_scale(player->dir, INTERACTION_REACH));
	return (world_cell(point));
}

void	handle_action_input(t_game *game)
{
	bool	pressed;

	pressed = mlx_is_key_down(game->mlx, MLX_KEY_SPACE);
	if (pressed && !game->ram->action_down)
		fire_toggle(game, action_target(&game->ram->player));
	game->ram->action_down = pressed;
}
