/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:24:00 by patrik            #+#    #+#             */
/*   Updated: 2025/08/17 11:02:27 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int	handle_char(va_list args)
{
	char	c;

	c = va_arg(args, int);
	ft_putchar_fd(c, 1);
	return (1);
}
