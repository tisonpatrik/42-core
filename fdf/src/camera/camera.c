/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:40:11 by ptison            #+#    #+#             */
/*   Updated: 2025/10/22 23:05:28 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/camera.h"

t_camera	init_camera_defaults(int width, int height)
{
	t_camera	camera;

	camera.alpha = 0.46373398 / 2;
	camera.beta = 0.46373398;
	camera.xrotate = 0;
	camera.yrotate = 0;
	camera.zrotate = 0;
	camera.x_offset = width / 2;
	camera.y_offset = height / 2;
	camera.zoom = 1;
	camera.zscale = 1;
	update_camera_trig_cache(&camera);
	return (camera);
}

void	reset_camera(t_camera *cam, int width, int height)
{
	cam->alpha = 0.46373398 / 2;
	cam->beta = 0.46373398;
	cam->xrotate = 0;
	cam->yrotate = 0;
	cam->zrotate = 0;
	cam->x_offset = width / 2;
	cam->y_offset = height / 2;
	cam->zoom = 1;
	cam->zscale = 1;
	update_camera_trig_cache(cam);
}

void	set_camera_isometric(t_camera *cam, int screen_w, int screen_h)
{
	cam->alpha = M_PI / 4.0;
	cam->beta = atan(1.0 / sqrt(2.0));
	cam->xrotate = 0.0;
	cam->yrotate = 0.0;
	cam->zrotate = 0.0;
	cam->zoom = 1.0;
	cam->zscale = 1.0;
	cam->x_offset = screen_w / 2;
	cam->y_offset = screen_h / 2;
	update_camera_trig_cache(cam);
}

void	update_camera_trig_cache(t_camera *cam)
{
	cam->sin_alpha = sin(cam->alpha);
	cam->cos_alpha = cos(cam->alpha);
	cam->sin_beta = sin(cam->beta);
	cam->cos_beta = cos(cam->beta);
	cam->sin_xrot = sin(cam->xrotate);
	cam->cos_xrot = cos(cam->xrotate);
	cam->sin_yrot = sin(cam->yrotate);
	cam->cos_yrot = cos(cam->yrotate);
	cam->sin_zrot = sin(cam->zrotate);
	cam->cos_zrot = cos(cam->zrotate);
}
