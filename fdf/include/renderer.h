/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:11:47 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 22:32:12 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef RENDERER_H
#define RENDERER_H


# include "../include/camera.h"
# include "../include/grid.h"

t_point2d_temp	project_point(t_point3d point, t_camera *camera);
void	display_menu(mlx_t *mlx);
void	draw_image(mlx_image_t *image, t_grid *grid, t_camera *camera);
void	draw_reset(mlx_image_t *image);
void	make_upper(unsigned int i, char *c);


void		rotate_x(double *y, double *z, double alpha);
void		rotate_y(double *x, double *z, double beta);
void		rotate_z(double *x, double *y, double gamma);
#endif
