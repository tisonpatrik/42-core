/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:14:50 by ptison            #+#    #+#             */
/*   Updated: 2025/10/22 23:20:20 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_H
# define GRID_H

# include "../include/camera.h"
# include "../include/utils.h"
# include "../lib/libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BACKGROUND 0x22222200
# define TEXT_COLOR 0xEAEAEAFF

typedef enum e_chars
{
	CHAR_SPACE = ' ',
	CHAR_NEWLINE = '\n',
	CHAR_CARRIAGE_RETURN = '\r',
	CHAR_NULL = '\0',
}				t_chars;

typedef struct s_point3d
{
	double		x;
	double		y;
	double		z;
	int			mapcolor;
}				t_point3d;

typedef struct s_grid
{
	t_point3d	**grid3d;
	int			rows;
	int			cols;
	int			high;
	int			low;
	t_arena		*arena;
}				t_grid;

typedef struct s_token_data
{
	int			z_value;
	uint32_t	color;
	bool		success;
}				t_token_data;

typedef struct s_grid_info
{
	int32_t		rows;
	int32_t		cols;
	double		interval;
	int			x_offset;
	int			y_offset;
}				t_grid_info;

bool			parse_grid_lines(const char *filename, t_grid *grid,
					t_grid_info *info);
t_grid_info		analyze_grid_file(const char *filename, int width, int height);
int				get_file_fd(const char *file_name);
t_grid			*allocate_grid(int rows, int cols);
t_grid			*create_grid_from_file(const char *filename, int width,
					int height);
void			free_grid(t_grid *grid);
bool			parse_grid_row(char **tokens, t_grid *grid, int row_index,
					t_grid_info *info);
t_token_data	parse_token(const char *token);
#endif
