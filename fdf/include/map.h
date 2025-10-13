/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:31:10 by ptison            #+#    #+#             */
/*   Updated: 2025/10/13 23:02:14 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../lib/libft/include/libft.h"
# include <fcntl.h>

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
typedef struct s_cell
{
	int			z;
	int			has_color;
	uint32_t	color;
}				t_cell;

typedef struct s_map_info
{
	int			count_rows;
	int			count_columns;
	int			fd;
}				t_map_info;

typedef struct s_view
{
	t_arena		*arena;
	t_cell		*cells;
	int			count_rows;
	int			count_columns;
}				t_map;

t_map			*read_map_from_file(const char *file_name);

t_map_info		*analyze_map_file(const char *file_name);

t_map_info		*allocate_map_info(int count_of_rows, int count_of_columns, int fd);
void			free_map_info(t_map_info *info);

t_map			*alocate_map(t_map_info *info);


void			free_map_arena(t_map *map);

size_t			calculate_arena_size(int nrows, int ncols);
int				setup_arena_layout(t_map *map, int nrows, int ncols);



int	parse_map(t_map *map, int fd);
void			free_map(t_map *map);

int				get_file_fd(const char *file_name);
int				count_tokens(char **tokens);
int				parse_token(const char *token);
#endif
