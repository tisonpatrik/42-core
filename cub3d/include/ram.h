/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ram.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:31:15 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:31:16 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAM_H
# define RAM_H

# include <stdbool.h>
# include <stdint.h>
# include "fire.h"
# include "orb.h"
# include "ray.h"
# include "vec2.h"

typedef struct s_player
{
	t_v2d	pos;
	t_v2d	dir;
	t_v2d	plane;
}	t_player;

typedef struct s_mouse_input
{
	int32_t	last_x;
	bool	initialized;
	bool	enabled;
}	t_mouse_input;

typedef struct s_ram
{
	uint8_t			*tiles;
	t_player		player;
	t_mouse_input	mouse;
	t_fire_system	fire;
	t_hit_buffer	fire_hits;
	t_orb_system	orbs;
	double			*sprite_depth;
	bool			action_down;
}	t_ram;

#endif
