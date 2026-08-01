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
	/* DDA distance is perpendicular to the camera plane, not Euclidean. */
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
	/* Distance to the next grid boundary and between equal-side crossings. */
	t_v2d		side_dist;
	t_v2d		delta_dist;
	t_v2i		step;
	t_ray_hit	wall;
}	t_ray;

#endif
