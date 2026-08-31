/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:29:26 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:29:27 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "ft_math.h"
#include "game.h"
#include "orb.h"

static bool	orb_is_visible(t_orb *orb, t_minimap_view *view,
	t_v2d *relative)
{
	*relative = ft_v2d_sub(orb->position,
			ft_v2i_to_v2d(view->first_tile));
	return (orb->active && relative->x >= 0.0 && relative->y >= 0.0
		&& relative->x < view->visible_tiles.x
		&& relative->y < view->visible_tiles.y);
}

void	minimap_draw_orbs(t_game *game, t_minimap_view *view)
{
	t_v2d	relative;
	t_v2i	position;
	size_t	i;
	int		size;
	int		half_size;

	size = view->tile_scale / 2;
	size = ft_max_int(size, 2);
	half_size = size / 2;
	i = 0;
	while (i < game->ram->orbs.count)
	{
		if (orb_is_visible(&game->ram->orbs.orbs[i], view, &relative))
		{
			position = minimap_world_to_pixel(view,
					game->ram->orbs.orbs[i].position);
			position.x -= half_size;
			position.y -= half_size;
			minimap_draw_rectangle(game, position, (t_v2i){size, size},
				minimap_color(MM_COLOR_ORB));
		}
		i++;
	}
}
