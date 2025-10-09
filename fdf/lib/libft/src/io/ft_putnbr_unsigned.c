/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:22:51 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/io.h"

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
