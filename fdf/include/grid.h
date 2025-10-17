/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:14:50 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 00:48:47 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPERIMENTAL_H
# define EXPERIMENTAL_H

# include "../include/camera.h"
# include "../lib/libft/include/libft.h"
# include <fcntl.h>
# include "../include/utils.h"
# include <errno.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>


typedef enum e_chars
{
	CHAR_SPACE = ' ',
	CHAR_NEWLINE = '\n',
	CHAR_CARRIAGE_RETURN = '\r',
	CHAR_NULL = '\0',
}				t_chars;


typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
}				t_point3d;


typedef struct s_grid
{
	t_point3d		**grid3d;
	int				rows;
	int				cols;
	int				high;
	int				low;
	t_arena			*arena;
}					t_grid;


typedef struct s_token_data
{
	int		z_value;
	uint32_t	color;
}	t_token_data;


typedef struct s_grid_info
{
	int32_t		rows;
	int32_t		cols;
	int32_t		fd;
}				t_grid_info;



int				count_tokens(char **tokens);
t_token_data	parse_token(const char *token);
t_grid			*allocate_grid(int rows, int cols);
t_grid_info		analyze_grid_file(const char *filename);
t_grid			*create_grid_from_file(const char *filename, int width, int height);
bool	parse_grid_row(char **tokens, t_grid *grid, int row_index, int width, int height);
void	free_grid(t_grid *grid);
#endif