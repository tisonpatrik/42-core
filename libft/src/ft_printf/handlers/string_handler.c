/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:30:00 by patrik            #+#    #+#             */
/*   Updated: 2025/06/15 14:24:14 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
