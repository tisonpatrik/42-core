/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:03:49 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 11:25:15 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

#include "../../include/io.h"
#include "../../include/str.h"

# include <stdarg.h>
#include <unistd.h>


int	handle_char(va_list args);
int	handle_string(va_list args);
int	handle_pointer(va_list args);
int	handle_decimal(va_list args);
int	handle_unsigned(va_list args);
int	handle_hex(char type, va_list args);
int	handle_percent(void);
int	dispatch_conversion(char type, va_list args);
char	parse_format(const char *format, int *i);
#endif