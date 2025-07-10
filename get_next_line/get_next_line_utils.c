/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:18:20 by ptison            #+#    #+#             */
/*   Updated: 2025/07/10 18:37:46 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "unistd.h"
#include <stddef.h>
#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;

	i = 0;
	d = (unsigned char *)dest;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	copy_size = old_size;
	if (new_size < old_size)
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

int	read_to_buffer(int fd, t_buffer *buffer)
{
	ssize_t	bytes_read;

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
