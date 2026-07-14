/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:24:32 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/io.h"

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
