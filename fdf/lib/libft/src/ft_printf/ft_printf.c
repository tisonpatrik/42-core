/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	dispatch_conversion(char type, va_list args)
{
	if (type == 'c')
		return (handle_char(args));
	else if (type == 's')
		return (handle_string(args));
	else if (type == 'p')
		return (handle_pointer(args));
	else if (type == 'd' || type == 'i')
		return (handle_decimal(args));
	else if (type == 'u')
		return (handle_unsigned(args));
	else if (type == 'x' || type == 'X')
		return (handle_hex(type, args));
	else if (type == '%')
		return (handle_percent());
	else
	{
		ft_putchar_fd('%', STDOUT_FILENO);
		ft_putchar_fd(type, STDOUT_FILENO);
		return (2);
	}
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		total;
	va_list	args;

	i = 0;
	total = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			total += dispatch_conversion(format[i + 1], args);
			i += 2;
		}
		else
		{
			ft_putchar_fd(format[i], STDOUT_FILENO);
			total++;
			i++;
		}
	}
	va_end(args);
	return (total);
}
