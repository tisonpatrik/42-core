/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:10:44 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 22:21:48 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_INTERNAL_H
# define GNL_INTERNAL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../../include/get_next_line.h"
# include <stddef.h>

typedef struct s_buffer
{
	char	data[BUFFER_SIZE + 1];
	size_t	pos;
	size_t	size;
}			t_buffer;

typedef struct s_line
{
	char	*data;
	size_t	size;
	size_t	pos;
}			t_line;

int			read_to_buffer(int fd, t_buffer *buffer);
size_t		find_newline_in_buffer(char *buffer, size_t start, size_t end);
void		copy_chunk_to_line(t_line *line, t_buffer *buffer,
				size_t chunk_size);
int			expand_line_buffer(t_line *line, size_t needed_size);
int			process_buffer_chunk(t_line *line, t_buffer *buffer);
#endif
