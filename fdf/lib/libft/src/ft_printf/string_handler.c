/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:37 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	handle_string(va_list args)
{
	char	*s;
	int		count;

	s = va_arg(args, char *);
	if (s == NULL)
		s = "(null)";
	count = ft_strlen(s);
	ft_putstr_fd(s, STDOUT_FILENO);
	return (count);
}
