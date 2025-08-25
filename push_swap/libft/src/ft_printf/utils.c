/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:49:37 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 12:39:29 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft/io.h"

void	ft_putnbr_unsigned(unsigned int n)
{
	int				digits;
	unsigned int	temp;
	int				i;

	digits = 1;
	temp = n;
	while (temp >= 10)
	{
		digits++;
		temp /= 10;
	}
	while (digits > 0)
	{
		temp = n;
		i = 1;
		while (i < digits)
		{
			temp /= 10;
			i++;
		}
		ft_putchar_fd((temp % 10) + '0', 1);
		digits--;
	}
}

void	ft_putnbr_hex(unsigned int n, int uppercase)
{
	char	*hex_digits;
	char	buffer[32];
	int		i;

	if (uppercase)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	i = 0;
	while (n >= 16)
	{
		buffer[i++] = hex_digits[n % 16];
		n /= 16;
	}
	buffer[i++] = hex_digits[n];
	while (i > 0)
		ft_putchar_fd(buffer[--i], 1);
}

void	ft_putptr(void *ptr)
{
	unsigned long	addr;
	char			*hex_digits;
	char			buffer[32];
	int				i;

	addr = (unsigned long)ptr;
	hex_digits = "0123456789abcdef";
	i = 0;
	while (addr >= 16)
	{
		buffer[i++] = hex_digits[addr % 16];
		addr /= 16;
	}
	buffer[i++] = hex_digits[addr];
	while (i > 0)
		ft_putchar_fd(buffer[--i], 1);
}
