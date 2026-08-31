/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:28:05 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:28:06 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator.h"
#include "game.h"
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
