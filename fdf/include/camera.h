/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:36:23 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 10:43:10 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "../lib/libft/include/libft.h"
# include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef struct s_pt2
{
	double	x;
	double	y;
}			t_pt2;

typedef struct s_camera
{
	double	interval;
}			t_camera;

t_camera	init_camera_defaults(void);

#endif
