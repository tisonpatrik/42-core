/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:04:31 by ptison            #+#    #+#             */
/*   Updated: 2025/06/15 14:12:13 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdarg.h>
#include <stddef.h>

char	parse_format(const char *format, int *i)
{
	char	type;

	type = format[*i];
	if (type == 'c' || type == 's' || type == 'p' || type == 'd' || type == 'i'
		|| type == 'u' || type == 'x' || type == 'X' || type == '%')
	{
		(*i)++;
		return (type);
	}
	return (0);
}
