/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:10:44 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_INTERNAL_H
# define GL_INTERNAL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include "../../../include/io.h"
# include "../../../include/mem.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_buffer
{
	char	data[BUFFER_SIZE];
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
