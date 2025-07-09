/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:30:00 by patrik            #+#    #+#             */
/*   Updated: 2025/06/19 17:41:34 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	ft_putnbr_unsigned(unsigned int n);

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
