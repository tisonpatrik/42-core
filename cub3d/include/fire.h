#ifndef FIRE_H
# define FIRE_H

# include <stdbool.h>
# include <stddef.h>
# include "cycle.h"
# include "vec2.h"

# define FIRE_ANIMATION_INTERVAL 0.05
# define FIRE_TRANSITION_SPEED 1.0
# define FIRE_FIRST_FRAME 16
# define FIRE_ALPHA_THRESHOLD 128
# define FIRE_MIN_DISTANCE 0.01

struct	s_game;

typedef enum e_fire_state
{
	FIRE_IDLE,
	FIRE_SHRINKING,
	FIRE_HIDDEN,
	FIRE_GROWING
}	t_fire_state;

typedef struct s_fire_cell
{
	t_fire_state	state;
	double			height;
}	t_fire_cell;

typedef struct s_fire_system
{
	t_fire_cell		*cells;
	size_t			count;
	t_step_cycle	animation;
}	t_fire_system;

/* Fire is a bonus-only transparent map cell, not a billboard sprite. */
void	fire_init(struct s_game *game);
void	fire_update(struct s_game *game, double delta_time);
void	fire_toggle(struct s_game *game, t_v2i map);
double	fire_height_at(const struct s_game *game, t_v2i map);
void	fire_update_cells(struct s_game *game, double delta_time);

#endif
