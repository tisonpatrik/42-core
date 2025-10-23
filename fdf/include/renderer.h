/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:11:47 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 15:16:48 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef RENDERER_H
#define RENDERER_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../include/camera.h"
# include "../include/grid.h"

# define WIDTH				1920
# define HEIGHT				1200
# define BACKGROUND			0x22222200
# define TEXT_COLOR			0xEAEAEAFF

typedef enum e_clip_sector {
	CLIP_LEFT   = 1 << 0,
	CLIP_RIGHT  = 1 << 1,
	CLIP_BOTTOM = 1 << 2,
	CLIP_TOP    = 1 << 3
} t_clip_sector;

typedef struct s_point2d_temp
{
	int		x;
	int		y;
	int		rgba;
}			t_point2d_temp;

typedef struct s_lod_params
{
	int	step;
	int	lod_cols;
	int	y;
}	t_lod_params;

typedef struct s_render_grid
{
	t_point2d_temp	*points;
	int				step;
	int				rows;
	int				cols;
}					t_render_grid;

typedef struct s_renderer {
    mlx_t       *mlx;
    mlx_image_t *img;
    int          width;
    int          height;
} t_renderer;

t_renderer	init_renderer(void);
void	display_menu(mlx_t *mlx);
void	render_image(mlx_image_t *image, t_grid *grid, t_camera *camera);
t_render_grid	create_render_grid(t_grid *grid, t_camera *camera);
int calculate_lod_step(int rows, int cols, double zoom);
void draw_line_between_points(mlx_image_t *image, t_point2d_temp a, t_point2d_temp b);
void	draw_grid_row(mlx_image_t *image, t_render_grid *render_grid, int y);

void		rotate_x(double *y, double *z, double sin_a, double cos_a);
void		rotate_y(double *x, double *z, double sin_b, double cos_b);
void		rotate_z(double *x, double *y, double sin_g, double cos_g);
#endif
