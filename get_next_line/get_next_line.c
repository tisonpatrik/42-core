/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:18:16 by ptison            #+#    #+#             */
/*   Updated: 2025/07/10 18:36:24 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int			read_to_buffer(int fd, t_buffer *buffer);
size_t		find_newline_in_buffer(char *buffer, size_t start, size_t end);
void		copy_chunk_to_line(t_line *line, t_buffer *buffer,
				size_t chunk_size);

static int	expand_line_buffer(t_line *line, size_t needed_size)
{
	size_t	new_size;
	char	*new_line;

	if (line->size == 0)
		new_size = needed_size;
	else
		new_size = line->size * 2;
	if (new_size < needed_size)
		new_size = needed_size;
	new_line = ft_realloc(line->data, line->size, new_size);
	if (!new_line)
	{
		free(line->data);
		return (0);
	}
	line->data = new_line;
	line->size = new_size;
	return (1);
}

static int	process_buffer_chunk(t_line *line, t_buffer *buffer)
{
	size_t	newline_pos;
	size_t	chunk_size;

	newline_pos = find_newline_in_buffer(buffer->data, buffer->pos,
			buffer->size);
	chunk_size = newline_pos - buffer->pos;
	if (newline_pos < buffer->size && buffer->data[newline_pos] == '\n')
		chunk_size++;
	if (line->pos + chunk_size + 1 > line->size)
	{
		if (!expand_line_buffer(line, line->pos + chunk_size + 1))
			return (0);
	}
	copy_chunk_to_line(line, buffer, chunk_size);
	line->pos += chunk_size;
	line->data[line->pos] = '\0';
	buffer->pos += chunk_size;
	return (1);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	t_line			line;

	line.data = NULL;
	line.size = 0;
	line.pos = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer.pos >= buffer.size)
		{
			if (!read_to_buffer(fd, &buffer))
				break ;
		}
		if (!process_buffer_chunk(&line, &buffer))
			return (NULL);
		if (buffer.pos > 0 && buffer.data[buffer.pos - 1] == '\n')
			break ;
	}
	return (line.data);
}
