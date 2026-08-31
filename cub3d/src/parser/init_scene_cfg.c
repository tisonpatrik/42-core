/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_cfg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 17:41:20 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/06 18:15:16 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_scene_cfg(t_scene_config *cfg)
{
	cfg->map_size = (t_v2i){0, 0};
	cfg->tiles = NULL;
	cfg->spawn_position = (t_v2d){0.0, 0.0};
	cfg->spawn_direction = (t_v2d){0.0, 0.0};
	cfg->camera_plane = (t_v2d){0.0, 0.0};
	cfg->wall_paths.north = NULL;
	cfg->wall_paths.south = NULL;
	cfg->wall_paths.west = NULL;
	cfg->wall_paths.east = NULL;
	cfg->floor_color = (t_rgba){0, 0, 0, 0};
	cfg->ceiling_color = (t_rgba){0, 0, 0, 0};
}
