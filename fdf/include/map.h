/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:31:10 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 12:58:18 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../lib/libft/include/libft.h"
# include "fcntl.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdint.h>

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
	bool		has_color;
	uint32_t	color;
}				t_cell;

typedef struct s_map
{
	t_cell		**rows;
	int			*cols;
	int			nrows;
	int			cap;
}				t_map;

void			map_push_row(t_map *map, t_cell *line_cells, int len);
void			map_free(t_map *map);
void			map_init(t_map *map);

t_map			get_map(char *file_name);

#endif
