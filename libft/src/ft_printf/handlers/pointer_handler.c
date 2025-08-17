/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:30:00 by patrik            #+#    #+#             */
/*   Updated: 2025/06/19 17:35:28 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	ft_putptr(void *ptr);

int	get_hex_count(unsigned long ptr)
{
	unsigned long	temp;
	int				hex_count;

	hex_count = 0;
	temp = ptr;
	if (temp == 0)
		hex_count = 1;
	else
	{
		while (temp > 0)
		{
			temp /= 16;
			hex_count++;
		}
	}
	return (hex_count);
}

int	handle_pointer(va_list args)
{
	void	*ptr;
	int		hex_count;

	ptr = va_arg(args, void *);
	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	hex_count = get_hex_count((unsigned long)ptr);
	ft_putptr(ptr);
	return (2 + hex_count);
}
