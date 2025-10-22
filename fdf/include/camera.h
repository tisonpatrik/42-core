/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:36:23 by ptison            #+#    #+#             */
/*   Updated: 2025/10/22 23:05:24 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CAMERA_H
# define CAMERA_H

# include <math.h>
# include "../lib/libft/include/libft.h"

typedef struct s_vec3 {
    double x;
    double y;
    double z;
} t_vec3;

typedef struct s_pt2 {
    double x;
    double y;
} t_pt2;


typedef struct s_camera
{
	int				x_offset;
	int				y_offset;
	double			interval;
	double			alpha;
	double			beta;
	double			xrotate;
	double			yrotate;
	double			zrotate;
	double			zoom;
	double			zscale;
	// Cached trigonometric values for performance
	double			sin_alpha;
	double			cos_alpha;
	double			sin_beta;
	double			cos_beta;
	double			sin_xrot;
	double			cos_xrot;
	double			sin_yrot;
	double			cos_yrot;
	double			sin_zrot;
	double			cos_zrot;
}					t_camera;

void set_camera_isometric(t_camera *cam, int screen_w, int screen_h);
t_camera	init_camera_defaults(int width, int height);
void	reset_camera(t_camera *cam, int width, int height);
void	update_camera_trig_cache(t_camera *cam);

#endif