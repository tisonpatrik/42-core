/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:27:59 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:28:01 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdlib.h>
#include "config.h"
#include "fire.h"
#include "io.h"
#include "orb.h"
#include "input.h"
#include "renderer.h"

static void	game_loop(void *parameter)
{
	t_game	*game;
	double	delta_time;

	game = parameter;
	delta_time = game->mlx->delta_time;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		return ;
	}
	if (delta_time > MAX_SIMULATION_STEP)
		delta_time = MAX_SIMULATION_STEP;
	handle_input(game, delta_time);
	if (game->rom->bonus_enabled)
	{
		fire_update(game, delta_time);
		orb_update(game, delta_time);
	}
	render_frame(game);
}

static int	engine_error(t_game *game, const char *operation)
{
	ft_putstr_fd("Error\nMLX failed during ", 2);
	ft_putstr_fd(operation, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(mlx_strerror(mlx_errno), 2);
	engine_shutdown(game);
	return (EXIT_FAILURE);
}

static int	engine_init(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
	if (!game->mlx)
		return (engine_error(game, "window initialization"));
	game->frame_buffer = mlx_new_image(game->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->frame_buffer
		|| mlx_image_to_window(game->mlx, game->frame_buffer, 0, 0) < 0
		|| !mlx_loop_hook(game->mlx, game_loop, game))
		return (engine_error(game, "frame buffer initialization"));
	mouse_look_init(game);
	mlx_key_hook(game->mlx, &tab_key_hook, game);
	return (EXIT_SUCCESS);
}

int	run_engine(t_game *game)
{
	if (engine_init(game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	mlx_loop(game->mlx);
	engine_shutdown(game);
	return (EXIT_SUCCESS);
}
