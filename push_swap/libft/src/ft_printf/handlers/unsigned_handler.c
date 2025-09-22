/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/printf.h"
#include <stdarg.h>

int	handle_unsigned(va_list args)
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
			temp /= 10;
			count++;
		}
	}
	ft_putnbr_unsigned(n);
	return (count);
}
