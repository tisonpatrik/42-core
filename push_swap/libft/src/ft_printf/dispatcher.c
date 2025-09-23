/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:34:55 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 11:17:25 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"


int	dispatch_conversion(char type, va_list args)
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
	return (0);
}
