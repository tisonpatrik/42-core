/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:35:10 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	handle_decimal(va_list args)
{
	int		n;
	int		count;
	long	temp;

	n = va_arg(args, int);
	count = 0;
	temp = n;
	if (n == 0)
		count = 1;
	else
	{
		if (temp < 0)
		{
			temp = -temp;
			count = 1;
		}
		while (temp > 0)
		{
			temp /= 10;
			count++;
		}
	}
	ft_putnbr_fd(n, STDOUT_FILENO);
	return (count);
}
