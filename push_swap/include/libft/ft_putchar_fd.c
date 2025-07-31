/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:08:23 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
