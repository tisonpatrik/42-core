/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:32:13 by ptison            #+#    #+#             */
/*   Updated: 2025/06/19 19:33:00 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	ft_putnbr_hex(unsigned int n, int uppercase);

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
