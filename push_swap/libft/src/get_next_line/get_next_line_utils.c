/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:18:20 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 22:22:02 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"
#include <stdlib.h>
#include <unistd.h>

int	read_to_buffer(int fd, t_buffer *buffer)
{
	size_t	bytes_read;

	bytes_read = read(fd, buffer->data, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (0);
	buffer->size = bytes_read;
	buffer->pos = 0;
	return (1);
}

size_t	find_newline_in_buffer(char *buffer, size_t start, size_t end)
{
	size_t	i;

	i = start;
	while (i < end && buffer[i] != '\n')
		i++;
	return (i);
}

void	copy_chunk_to_line(t_line *line, t_buffer *buffer, size_t chunk_size)
{
	size_t	j;

	j = 0;
	while (j < chunk_size)
	{
		line->data[line->pos + j] = buffer->data[buffer->pos + j];
		j++;
	}
}

int	expand_line_buffer(t_line *line, size_t needed_size)
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

int	process_buffer_chunk(t_line *line, t_buffer *buffer)
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
