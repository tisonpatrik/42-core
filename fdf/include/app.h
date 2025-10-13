/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:16 by ptison            #+#    #+#             */
/*   Updated: 2025/10/13 23:11:17 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
#include <unistd.h>


# define WIDTH				1920
# define HEIGHT				1200


// # define TEXT_COLOR			0x11111b
// # define BACKGROUND			0x1e1e2e
// # define MENU_BACKGROUND		0xcdd6f4

// # define DARK_GREY			0x45475a
// # define Pink			0xf38ba8
// # define Green		0xa6e3a1
// # define Yellow		0xf9e2af
// # define Blue			0x89b4fa
// # define Pink			0xf5c2e7
// # define Teal			0x94e2d5
// # define Light_gray		0xa6adc8
// # define Darker_gray			0x585b70
// # define Light_blue_gray			0xbac2de

# define TEXT_COLOR			0xEAEAEAFF
# define BACKGROUND			0x22222200
# define MENU_BACKGROUND	0x1E1E1EFF
# define COLOR_TEN			0x9e0142ff
# define COLOR_NINE			0xd53e4fff
# define COLOR_EIGHT		0xf46d43ff
# define COLOR_SEVEN		0xfdae61ff
# define COLOR_SIX			0xfee08bff
# define COLOR_FIVE			0xe6f598ff
# define COLOR_FOUR			0xabdda4ff
# define COLOR_THREE		0x66c2a5ff
# define COLOR_TWO			0x3288bdff
# define COLOR_ONE			0x5e4fa2ff

# define MALLOC				"Malloc failed"
# define INVALID_MAP		"Map is invalid"
# define FILE_ERROR			"Unable to open file"

typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
	int		zcolor;
}				t_point3d;

typedef struct s_point2d
{
	int		x;
	int		y;
	int		z;
	int		rgba;
}			t_point2d;

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
}					t_camera;

typedef struct s_grid_info
{
	int				rows;
	int				cols;
	int				high;
	int				low;
}					t_grid_info;

typedef struct s_grid
{
	t_point3d		**grid3d;
	t_point2d		**grid2d;
}					t_grid;

typedef struct s_view
{
	t_camera		camera;
	t_grid_info		grid_info;
	t_grid			grid;
}					t_view;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_view		*map;
	mlx_image_t	*image;
}				t_fdf;

/* map_init.c */
void		init_map(t_view *map);
void		malloc_grid(t_view *map);
t_view		*parse_input(char *filename);
/* map_parser.c */
int			hex_to_int(const char *hex_str);
int			parse_color(int fd, t_view *map, char *tabj);
void		parse_column(int fd, t_view *map, char **tab, int i);
void		parse_map(int fd, t_view *map);
int			get_cols(int fd, t_view *map, char *line);
void		get_dimensions(int fd, t_view *map);
/* fdf_error.c */
void		ft_free_tab(void **ptr, size_t len);
void		free_map(t_view *map);
void		handle_error(const char *message);
void		error_map(int fd, t_view *map, char *message);
/* fdf_draw.c */
void		project(t_view *map, int i, int j);
void		draw_image(void *param);
void		display_menu(mlx_t *mlx);
/* fdf_rotate.c */
void		rotate_x(double *y, double *z, double alpha);
void		rotate_y(double *x, double *z, double beta);
void		rotate_z(double *x, double *y, double gamma);
/* fdf_init.c */
t_fdf		*init_fdf(char *filename);
/* fdf_app.c */
void		run_app(t_fdf *fdf);
/* fdf_hooks.c */
void		ft_hook(void *param);
void		fdf_scrollhook(double xdelta, double ydelta, void *param);
void		ft_hook_rotate(void *param);
void		ft_hook_project(void *param);
/* fdf_utils.c*/
void		make_upper(unsigned int i, char *c);
void		draw_reset(mlx_image_t *image);
/* fdf_color.c */
int			get_color(t_point2d current, t_point2d a, t_point2d b);
void		set_zcolor(t_view *map);

#endif