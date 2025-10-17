/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heightmap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:31:10 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 00:12:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEIGHTMAP_H
# define HEIGHTMAP_H

# include "../lib/libft/include/libft.h"
# include <fcntl.h>
# include "../include/utils.h"
# include <errno.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_chars
{
	CHAR_SPACE = ' ',
	CHAR_NEWLINE = '\n',
	CHAR_CARRIAGE_RETURN = '\r',
	CHAR_NULL = '\0',
}				t_chars;

typedef struct s_token_data
{
	int		z_value;
	uint32_t	color;
}	t_token_data;


typedef struct s_point
{
	int32_t			x;
	int32_t			y;
	int32_t			z;
	uint32_t  color;
}				t_point;

typedef struct s_heightmap
{
    t_arena  *arena;
    t_point  *points;
    size_t    rows;
    size_t    cols;
    int32_t   zmin;
    int32_t   zmax;
}			t_heightmap;


typedef struct s_heightmap_info
{
	int32_t			expected_count_rows;
	int32_t			expected_count_columns;
	int32_t			fd;
}				t_heightmap_info;



t_heightmap		*read_heightmap_from_file(const char *file_name);

t_heightmap_info	*analyze_heightmap_file(const char *file_name);

t_heightmap_info	*allocate_heightmap_info(int count_of_rows, int count_of_columns, int fd);
void			free_heightmap_info(t_heightmap_info *info);

t_heightmap		*allocate_heightmap(t_heightmap_info *info);


void			free_heightmap_arena(t_heightmap *heightmap);

size_t			calculate_arena_size(int nrows, int ncols);
int				setup_arena_layout(t_heightmap *heightmap, int nrows, int ncols);



bool			parse_heightmap(t_heightmap *heightmap, int fd);
void			free_heightmap(t_heightmap *heightmap);

int				get_file_fd(const char *file_name);
int				count_tokens(char **tokens);
t_token_data	parse_token(const char *token);
#endif
