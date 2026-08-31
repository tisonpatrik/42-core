/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:28:16 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:28:17 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "allocator.h"
#include "build_profile.h"
#include "game.h"
#include "fire.h"
#include "io.h"
#include "orb.h"
#include "parser.h"

static int	setup_rom(t_game *game, const t_scene_config *config,
	bool bonus_enabled)
{
	game->rom = ft_arena_push(game->arena, sizeof(t_rom));
	if (!game->rom)
		return (EXIT_FAILURE);
	game->rom->map_size = config->map_size;
	game->rom->floor_color = config->floor_color;
	game->rom->ceiling_color = config->ceiling_color;
	game->rom->bonus_enabled = bonus_enabled;
	return (textures_load(&game->rom->textures, config, bonus_enabled));
}

static void	setup_player(t_player *player, const t_scene_config *config)
{
	player->pos = config->spawn_position;
	player->dir = config->spawn_direction;
	player->plane = config->camera_plane;
}

static int	setup_failed(t_game *game)
{
	game_cleanup(game);
	return (EXIT_FAILURE);
}

/* Bonus objects are derived only after parser tiles have been copied to RAM. */
static int	setup_runtime_bonus(t_game *game)
{
	fire_init(game);
	if (orb_init(game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	game_setup(t_game *game, const t_scene_config *config)
{
	bool	bonus_enabled;
	size_t	memory_size;

	bonus_enabled = CUB_BONUS_ENABLED;
	if (!game || !config
		|| !game_memory_size(config, bonus_enabled, &memory_size)
		|| !valid_scene_config(config, bonus_enabled))
	{
		ft_putendl_fd("Error\nInvalid scene configuration.", 2);
		return (EXIT_FAILURE);
	}
	game->arena = ft_arena_create(memory_size);
	if (!game->arena)
		return (ft_putendl_fd("Error\nMemory allocation failed.", 2),
			EXIT_FAILURE);
	if (setup_rom(game, config, bonus_enabled) != EXIT_SUCCESS
		|| setup_ram(game, config, bonus_enabled) != EXIT_SUCCESS)
		return (setup_failed(game));
	setup_player(&game->ram->player, config);
	if (bonus_enabled && setup_runtime_bonus(game) != EXIT_SUCCESS)
		return (setup_failed(game));
	return (EXIT_SUCCESS);
}
