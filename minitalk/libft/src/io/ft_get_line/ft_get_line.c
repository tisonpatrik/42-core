/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:18:16 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_internal.h"

char	*ft_get_line(int fd)
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
			{
				if (line.data == NULL)
					return (NULL);
				break ;
			}
		}
		if (!process_buffer_chunk(&line, &buffer))
			return (NULL);
		if (buffer.pos > 0 && buffer.data[buffer.pos - 1] == '\n')
			break ;
	}
	return (line.data);
}
