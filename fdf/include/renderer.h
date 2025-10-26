/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:11:47 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 18:27:22 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "../include/camera.h"
# include "../include/grid.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>

# define COS_45 0.70710678118
# define SIN_30 0.5

# define WIDTH 1920
# define HEIGHT 1200
# define BACKGROUND 0x22222200
# define TEXT_COLOR 0xEAEAEAFF

typedef struct s_bresenham_state
{
	int			current_x;
	int			current_y;
	int			target_x;
	int			target_y;
	int			delta_x;
	int			delta_y;
	int			step_x;
	int			step_y;
	int			error_accumulator;
	int			color;
}				t_bresenham_state;

typedef struct s_point2d
{
	int			x;
	int			y;
	int			rgba;
}				t_point2d;

typedef struct s_render_grid
{
	t_point2d	*points;
	int			rows;
	int			cols;
	t_arena		*arena;
}				t_render_grid;

typedef struct s_renderer
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;
}				t_renderer;

t_renderer		init_renderer(void);
void			display_menu(mlx_t *mlx);
void			render_image(mlx_image_t *image, t_grid *grid);
t_render_grid	allocate_render_grid(int rows, int cols);
t_render_grid	create_render_grid(t_grid *grid);
void			free_render_grid(t_render_grid *render_grid);
void			draw_line_between_points(mlx_image_t *image,
					t_point2d start_point, t_point2d end_point);
void			draw_grid_row(mlx_image_t *image, t_render_grid *render_grid,
					int y);
#endif
