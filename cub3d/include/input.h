/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:31:00 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:31:04 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define MOVE_SPEED 3.0
# define ROTATION_SPEED 2.0
# define MOUSE_SENSITIVITY 0.0025
# define COLLISION_MARGIN 0.15
# define MAX_SIMULATION_STEP 0.05

# include "vec2.h"
# include "MLX42.h"

struct	s_game;
struct	s_player;

void	handle_input(struct s_game *game, double delta_time);
void	handle_action_input(struct s_game *game);
void	mouse_look_init(struct s_game *game);
double	mouse_look_angle(struct s_game *game);
void	move_player(struct s_game *game, t_v2d movement);
void	tab_key_hook(mlx_key_data_t keydata, void *param);

#endif
