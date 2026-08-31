/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:29:05 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:29:06 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "game.h"

void	mouse_look_init(t_game *game)
{
	if (!game->rom->bonus_enabled)
		return ;
	game->ram->mouse.last_x = 0;
	game->ram->mouse.initialized = false;
	game->ram->mouse.enabled = true;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
}

double	mouse_look_angle(t_game *game)
{
	t_mouse_input	*mouse;
	int32_t			x;
	int32_t			y;
	double			delta_x;

	mouse = &game->ram->mouse;
	if (!game->rom->bonus_enabled || !mouse->enabled)
		return (0.0);
	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (!mouse->initialized)
	{
		mouse->last_x = x;
		mouse->initialized = true;
		return (0.0);
	}
	delta_x = (double)x - (double)mouse->last_x;
	mouse->last_x = x;
	return (delta_x * MOUSE_SENSITIVITY);
}

static void	mouse_toggle(t_game *game)
{
	t_mouse_input	*mouse;

	if (!game->rom->bonus_enabled)
		return ;
	mouse = &game->ram->mouse;
	if (mouse->enabled)
	{
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
		mouse->enabled = false;
	}
	else
	{
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		mouse->enabled = true;
		mouse->initialized = false;
	}
}

void	tab_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
		mouse_toggle(game);
}
