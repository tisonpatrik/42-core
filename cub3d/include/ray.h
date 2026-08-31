/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:31:23 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:31:24 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <stddef.h>
# include "vec2.h"

# define DELTA_INFINITY 1e30

typedef enum e_hit_side
{
	HIT_X,
	HIT_Y
}	t_hit_side;

typedef struct s_ray_hit
{
	t_v2i		map;
	double		distance;
	t_hit_side	side;
	double		wall_x;
}	t_ray_hit;

typedef struct s_hit_buffer
{
	t_ray_hit	*items;
	size_t		count;
	size_t		capacity;
}	t_hit_buffer;

typedef struct s_ray
{
	t_v2d		dir;
	t_v2i		map;
	t_v2d		side_dist;
	t_v2d		delta_dist;
	t_v2i		step;
	t_ray_hit	wall;
}	t_ray;

#endif
