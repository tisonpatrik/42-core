/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/io.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd);

/**
 * @brief Outputs a string to a file descriptor, followed by a newline
 *
 * This function writes a string to the specified file descriptor,
 * followed by a newline character. It uses ft_putstr_fd to output
 * the string. If the string is NULL, only a newline is output.
 *
 * @param s The string to output
 * @param fd The file descriptor to write to
 */
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

/*
int	main(void)
{
	char	*str;

	str = "hello";
	ft_putendl_fd(str, 1);
	return (0);
}
*/
