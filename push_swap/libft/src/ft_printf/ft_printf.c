/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 11:18:44 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"


int	ft_printf(const char *format, ...)
{
	int		i;
	int		total;
	va_list	args;
	char	type;

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
			ft_putchar_fd(format[i], STDOUT_FILENO);
			total++;
			i++;
		}
	}
	va_end(args);
	return (total);
}
