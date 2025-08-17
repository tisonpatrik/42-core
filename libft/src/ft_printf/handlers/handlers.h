/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:30:00 by patrik            #+#    #+#             */
/*   Updated: 2025/06/15 16:20:25 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

# include <stdarg.h>

int	handle_char(va_list args);
int	handle_string(va_list args);
int	handle_pointer(va_list args);
int	handle_decimal(va_list args);
int	handle_unsigned(va_list args);
int	handle_hex(char type, va_list args);
int	handle_percent(void);

#endif