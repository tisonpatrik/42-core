/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:34 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/io.h"
#include <unistd.h>

/**
 * @brief Outputs a character to a file descriptor
 *
 * This function writes a single character to the specified file descriptor.
 * It uses the write system call to output the character.
 *
 * @param c The character to output
 * @param fd The file descriptor to write to
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
int	main(void)
{
	char	c;
	int		fd;

	c = 't';
	fd = 1;
	ft_putchar_fd(c, fd);
	ft_putchar_fd('\n', fd);
	return (0);
}
*/
