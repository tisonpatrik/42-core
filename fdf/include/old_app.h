/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_app.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:16 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 23:50:28 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OLD_APP_H
# define OLD_APP_H

# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../include/heightmap.h"
# include "../include/camera.h"
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
#include <unistd.h>
# include "../include/color.h"
# include "../include/renderer.h"

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





typedef struct s_fdf
{
	mlx_t		*mlx;
	t_view		*view;
	mlx_image_t	*image;
}				t_fdf;

/* grid_allocator.c */
int			allocate_grid_memory(t_view *view);
void		free_grid_memory(t_view *view);
/* map_initializer.c */
void		init_grid_defaults(t_grid *grid);
void		init_map_defaults(t_view *view);
void		calculate_camera_interval(t_view *view);
/* grid_factory.c */
t_view		*create_view(void);
t_view		*create_map_from_file(const char *filename);
void		destroy_map(t_view *view);

/* file_reader.c */
char		**read_map_file_lines_from_fd(int fd, int *line_count);
void		free_map_lines(char **lines);
/* data_validator.c */
int			hex_to_int(const char *hex_str);
int			parse_color_from_token(char *token);
int			validate_map_line(char *line);
int			get_column_count(char *line);
/* data_builder.c */
void		build_point3d(t_point3d *point, int row, int col, int z_value, t_grid *grid, t_camera *camera);
void		build_column_from_tokens(char **tokens, t_grid *grid, t_camera *camera, int row);
/* map_orchestrator.c */
int			parse_map_from_lines(char **lines, int line_count, t_view *view);
int			get_map_dimensions(char **lines, int line_count, t_view *view);
/* map_parser.c */
void		parse_map_for_view(int fd, t_view *view);
void		get_dimensions(int fd, t_view *view);
int			get_cols(int fd, t_view *view, char *line);
/* fdf_error.c */
void		ft_free_tab(void **ptr, size_t len);
void		free_view(t_view *view);
void		handle_error(const char *message);
void		error_map(int fd, t_view *view, char *message);


/* fdf_init.c */
t_fdf		*init_fdf(char *filename);
/* fdf_app.c */
void		run_fdf(t_fdf *fdf);
/* fdf_hooks.c */
void		ft_hook(void *param);
void		fdf_scrollhook(double xdelta, double ydelta, void *param);
void		ft_hook_rotate(void *param);
void		ft_hook_project(void *param);


#endif