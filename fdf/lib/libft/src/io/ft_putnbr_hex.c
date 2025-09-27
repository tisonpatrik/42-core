/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:24:01 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:38 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/io.h"

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
