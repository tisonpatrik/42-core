/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experimental.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:14:50 by ptison            #+#    #+#             */
/*   Updated: 2025/10/16 15:08:31 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPERIMENTAL_H
# define EXPERIMENTAL_H

# include "../include/app.h"
# include "../include/map.h"

void set_camera_isometric(t_camera *cam, int screen_w, int screen_h);
t_grid	*allocate_grid(int rows, int cols);
t_grid	*get_grid(t_map *map);
void	free_grid(t_view *view);
#endif