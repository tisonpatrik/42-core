#ifndef INPUT_H
# define INPUT_H

# define MOVE_SPEED 3.0
# define ROTATION_SPEED 2.0
# define COLLISION_MARGIN 0.15
# define MAX_SIMULATION_STEP 0.05

# include "vec2.h"

struct	s_game;
struct	s_player;

/* Applies frame-rate-independent rotation and normalized collision movement. */
void	handle_input(struct s_game *game, double delta_time);
void	handle_action_input(struct s_game *game);
void	move_player(struct s_game *game, t_v2d movement);

#endif
