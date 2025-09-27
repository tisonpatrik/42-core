/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:47:38 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:32 by ptison           ###   ########.fr       */
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

char		*get_next_line(int fd);

#endif
