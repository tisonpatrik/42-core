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

typedef struct s_map
{
	t_arena		*arena;
	t_cell		*cells;
	int			*row_counts;
	int			*row_offsets;
	int			nrows;
	int			total_cells;
}				t_map;
void free_map_arena(t_map *map);
t_map *build_map_arena_from_file(const char *path);
#endif
