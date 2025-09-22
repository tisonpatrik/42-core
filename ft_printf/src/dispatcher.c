/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:58:46 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 11:02:00 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers/handlers.h"
#include <stdarg.h>

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
