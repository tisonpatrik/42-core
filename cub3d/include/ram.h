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

typedef struct s_ram
{
	uint8_t			*tiles;
	t_player		player;
	t_fire_system	fire;
	t_hit_buffer	fire_hits;
	t_orb_system	orbs;
	double			*sprite_depth;
	bool			action_down;
}	t_ram;

#endif
