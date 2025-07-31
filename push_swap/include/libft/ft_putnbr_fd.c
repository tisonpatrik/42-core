/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:09:45 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 07:59:59 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

/**
 * @brief Outputs an integer to a file descriptor
 *
 * This function writes an integer to the specified file descriptor.
 * It handles negative numbers and the minimum integer value correctly.
 * The number is converted to a string and output digit by digit.
 *
 * @param n The integer to output
 * @param fd The file descriptor to write to
 */
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

/*
int	main(void)
{
	int	n;

	n = 666;
	ft_putnbr_fd(n, 1);
	return (0);
}
*/
