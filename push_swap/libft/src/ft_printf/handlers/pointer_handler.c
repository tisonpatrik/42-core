/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 13:35:39 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/io.h"
#include "../../../include/printf.h"
#include <stdarg.h>
#include <stdlib.h>

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
