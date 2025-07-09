/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:25:51 by ptison            #+#    #+#             */
/*   Updated: 2025/06/15 14:14:05 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdarg.h>

int	dispatch_conversion(char type, va_list args);

int	ft_printf(const char *format, ...)
{
	int			i;
	int			total;
	va_list		args;
	char		type;

	i = 0;
	total = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			type = parse_format(format, &i);
			total += dispatch_conversion(type, args);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			total++;
			i++;
		}
	}
	va_end(args);
	return (total);
}
