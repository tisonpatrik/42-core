/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:47:38 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:28:25 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

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

void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int			read_to_buffer(int fd, t_buffer *buffer);
size_t		find_newline_in_buffer(char *buffer, size_t start, size_t end);
void		copy_chunk_to_line(t_line *line, t_buffer *buffer,
				size_t chunk_size);
char		*get_next_line(int fd);

#endif
