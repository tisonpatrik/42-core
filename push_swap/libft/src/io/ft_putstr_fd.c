/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 12:35:12 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/io.h"

void	ft_putchar_fd(char c, int fd);

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
