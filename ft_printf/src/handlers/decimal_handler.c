/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:30:00 by patrik            #+#    #+#             */
/*   Updated: 2025/06/19 15:56:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int	handle_decimal(va_list args)
{
	int		n;
	int		count;
	long	temp;

	n = va_arg(args, int);
	count = 0;
	temp = n;
	if (n < 0)
		count = 1;
	if (n == 0)
		count = 1;
	else
	{
		if (temp < 0)
			temp = -temp;
		while (temp > 0)
		{
			temp /= 10;
			count++;
		}
	}
	ft_putnbr_fd(n, 1);
	return (count);
}
