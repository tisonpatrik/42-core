/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 11:19:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	handle_hex(char type, va_list args)
{
	unsigned int	n;
	int				count;
	unsigned int	temp;

	n = va_arg(args, unsigned int);
	count = 0;
	temp = n;
	if (n == 0)
		count = 1;
	else
	{
		while (temp > 0)
		{
			temp /= 16;
			count++;
		}
	}
	ft_putnbr_hex(n, (type == 'X'));
	return (count);
}
