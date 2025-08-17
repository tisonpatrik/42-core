/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft/io.h"
#include "../../../include/ft/str.h"
#include <stdarg.h>

int	handle_string(va_list args)
{
	char	*s;
	int		count;

	s = va_arg(args, char *);
	if (s == NULL)
		s = "(null)";
	count = ft_strlen(s);
	ft_putstr_fd(s, 1);
	return (count);
}
