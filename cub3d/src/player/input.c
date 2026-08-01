#include "input.h"
#include "ft_math.h"
#include "game.h"
#include "vec2.h"

static int	key_axis(t_game *game, keys_t positive, keys_t negative)
{
	return (mlx_is_key_down(game->mlx, positive)
		- mlx_is_key_down(game->mlx, negative));
}

static t_v2d	movement_direction(t_game *game)
{
	t_v2d	forward;
	t_v2d	right;
	t_v2d	movement;

	forward = game->ram->player.dir;
	right = ft_v2d_perpendicular(forward);
	movement = ft_v2d_scale(forward,
			key_axis(game, MLX_KEY_W, MLX_KEY_S));
	movement = ft_v2d_add(movement, ft_v2d_scale(right,
				key_axis(game, MLX_KEY_D, MLX_KEY_A)));
	if (ft_v2d_length_squared(movement) > 1.0)
		movement = ft_v2d_normalize(movement);
	return (movement);
}

static void	rotate_player(t_player *player, double angle)
{
	if (angle == 0.0)
		return ;
	player->dir = ft_v2d_rotate(player->dir, angle);
	player->plane = ft_v2d_rotate(player->plane, angle);
}

void	handle_input(t_game *game, double delta_time)
{
	int		rotation_axis;
	double	step;

	delta_time = ft_clamp_double(delta_time, 0.0, MAX_SIMULATION_STEP);
	rotation_axis = key_axis(game, MLX_KEY_RIGHT, MLX_KEY_LEFT);
	rotate_player(&game->ram->player,
		rotation_axis * ROTATION_SPEED * delta_time);
	step = MOVE_SPEED * delta_time;
	move_player(game, ft_v2d_scale(movement_direction(game), step));
	if (game->rom->bonus_enabled)
		handle_action_input(game);
}
