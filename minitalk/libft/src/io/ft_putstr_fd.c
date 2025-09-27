/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/io.h"

/**
 * @brief Outputs a string to a file descriptor
 *
 * This function writes a string to the specified file descriptor.
 * It outputs each character of the string using ft_putchar_fd.
 * If the string is NULL, nothing is output.
 *
 * @param s The string to output
 * @param fd The file descriptor to write to
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}
