/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:29:32 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:30:17 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include <math.h>
#include "config.h"
#include "game.h"
#include "orb.h"
#include "vec2.h"

static size_t	collect_active_orbs(t_game *game, t_orb **orbs)
{
	t_orb_system	*system;
	size_t			i;
	size_t			count;

	system = &game->ram->orbs;
	i = 0;
	count = 0;
	while (i < system->count)
	{
		if (system->orbs[i].active)
		{
			orbs[count] = &system->orbs[i];
			count++;
		}
		i++;
	}
	return (count);
}

static void	sort_farthest_first(t_orb **orbs, size_t count, t_v2d origin)
{
	t_orb	*temporary_orb;
	double	temporary_distance;
	size_t	i;
	size_t	j;

	i = 1;
	while (i < count)
	{
		temporary_orb = orbs[i];
		temporary_distance = ft_v2d_distance_squared(
				temporary_orb->position, origin);
		j = i;
		while (j > 0 && ft_v2d_distance_squared(orbs[j - 1]->position,
				origin) < temporary_distance)
		{
			orbs[j] = orbs[j - 1];
			j--;
		}
		orbs[j] = temporary_orb;
		i++;
	}
}

static bool	project_orb(t_game *game, t_orb *orb, t_orb_projection *draw)
{
	t_player	*player;
	t_v2d		relative;
	t_v2d		camera;
	int			center_x;

	player = &game->ram->player;
	relative = ft_v2d_sub(orb->position, player->pos);
	if (!ft_v2d_basis_coordinates(relative, player->plane,
			player->dir, &camera))
		return (false);
	if (camera.y <= RENDER_NEAR_DISTANCE)
		return (false);
	draw->depth = camera.y;
	draw->size = (int)fabs(WINDOW_HEIGHT / camera.y * ORB_WORLD_SCALE);
	center_x = (int)(WINDOW_WIDTH * 0.5 * (1.0 + camera.x / camera.y));
	draw->left = center_x - draw->size / 2;
	draw->right = draw->left + draw->size - 1;
	draw->top = WINDOW_HEIGHT / 2 - draw->size / 2;
	draw->bottom = draw->top + draw->size - 1;
	return (draw->size > 0 && draw->right >= 0 && draw->left < WINDOW_WIDTH);
}

void	render_orbs(t_game *game)
{
	t_orb				*orbs[ORB_MAX_COUNT];
	t_orb_projection	projection;
	size_t				count;
	size_t				i;

	count = collect_active_orbs(game, orbs);
	sort_farthest_first(orbs, count, game->ram->player.pos);
	i = 0;
	while (i < count)
	{
		if (project_orb(game, orbs[i], &projection))
			draw_projected_orb(game, &projection);
		i++;
	}
}
