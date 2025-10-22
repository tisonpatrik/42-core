/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:11:47 by ptison            #+#    #+#             */
/*   Updated: 2025/10/22 23:05:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef RENDERER_H
#define RENDERER_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../include/camera.h"
# include "../include/grid.h"
# include "../include/color.h"

# define WIDTH				1920
# define HEIGHT				1200

typedef struct s_renderer {
    mlx_t       *mlx;
    mlx_image_t *img;
    int          width;
    int          height;
} t_renderer;

t_renderer	init_renderer(void);
void	display_menu(mlx_t *mlx);
void	draw_image_fast(mlx_image_t *image, t_grid *grid, t_camera *camera);

void		rotate_x(double *y, double *z, double sin_a, double cos_a);
void		rotate_y(double *x, double *z, double sin_b, double cos_b);
void		rotate_z(double *x, double *y, double sin_g, double cos_g);
#endif
