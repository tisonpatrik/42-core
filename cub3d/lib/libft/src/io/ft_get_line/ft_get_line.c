#include "io.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_math.h"
#include "mem.h"
#include "str8.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

static bool	refill(int fd, uint8_t *buffer, t_str8 *unread)
{
	ssize_t	size;

	size = read(fd, buffer, BUFFER_SIZE);
	if (size <= 0)
		return (false);
	*unread = (t_str8){buffer, (size_t)size};
	return (true);
}

static t_str8	next_chunk(t_str8 *unread)
{
	t_str8	chunk;
	size_t	length;

	length = 0;
	while (length < unread->len && unread->str[length] != '\n')
		length++;
	if (length < unread->len)
		length++;
	chunk = (t_str8){unread->str, length};
	unread->str += length;
	unread->len -= length;
	return (chunk);
}

static bool	grow_line(t_str8 *line, size_t *capacity, size_t needed)
{
	size_t	new_capacity;
	void	*memory;

	new_capacity = *capacity;
	if (new_capacity == 0)
		new_capacity = needed;
	while (new_capacity < needed && new_capacity <= SIZE_MAX / 2)
		new_capacity *= 2;
	if (new_capacity < needed)
		return (false);
	memory = ft_realloc(line->str, *capacity, new_capacity);
	if (!memory)
		return (false);
	line->str = memory;
	*capacity = new_capacity;
	return (true);
}

static bool	append_chunk(t_str8 *line, size_t *capacity, t_str8 chunk)
{
	size_t	needed;

	if (!ft_size_add(line->len, chunk.len, &needed)
		|| !ft_size_add(needed, 1, &needed))
		return (false);
	if (needed > *capacity && !grow_line(line, capacity, needed))
		return (false);
	ft_memcpy(line->str + line->len, chunk.str, chunk.len);
	line->len += chunk.len;
	line->str[line->len] = '\0';
	return (true);
}

char	*ft_get_line(int fd)
{
	static uint8_t	buffer[BUFFER_SIZE];
	static t_str8	unread;
	t_str8			line;
	t_str8			chunk;
	size_t			capacity;

	line = (t_str8){NULL, 0};
	capacity = 0;
	while (fd >= 0)
	{
		if (unread.len == 0 && !refill(fd, buffer, &unread))
			break ;
		chunk = next_chunk(&unread);
		if (!append_chunk(&line, &capacity, chunk))
			return (free(line.str), NULL);
		if (chunk.len > 0 && chunk.str[chunk.len - 1] == '\n')
			break ;
	}
	return ((char *)line.str);
}
