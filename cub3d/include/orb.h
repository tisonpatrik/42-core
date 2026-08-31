/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:31:12 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:31:12 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ORB_H
# define ORB_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include "cycle.h"
# include "vec2.h"

# define ORB_MAX_COUNT 5
# define ORB_ATLAS_COLUMNS 4
# define ORB_ATLAS_ROWS 4
# define ORB_FRAME_COUNT 16
# define ORB_FRAME_INTERVAL 0.08
# define ORB_WORLD_SCALE 0.55
# define ORB_PICKUP_RADIUS 0.4
# define ORB_ALPHA_THRESHOLD 32
# define ORB_CANDIDATES_PER_ORB 100
# define ORB_NEAR_MIN_DISTANCE_SQUARED 4.0
# define ORB_NEAR_MAX_DISTANCE_SQUARED 36.0
# define ORB_MIN_SPACING_SQUARED 4.0

struct	s_game;

typedef struct s_orb
{
	t_v2d	position;
	bool	active;
}	t_orb;

typedef struct s_orb_system
{
	t_orb			orbs[ORB_MAX_COUNT];
	size_t			count;
	size_t			collected;
	t_step_cycle	animation;
}	t_orb_system;

int			orb_init(struct s_game *game);
void		orb_update(struct s_game *game, double delta_time);
uint32_t	orb_seed(struct s_game *game);
bool		orb_generate(struct s_game *game, uint32_t seed);
size_t		orb_select_positions(struct s_game *game, t_v2i *candidates,
				size_t candidate_count, uint32_t seed);
void		orb_collect_nearby(struct s_game *game);

#endif
