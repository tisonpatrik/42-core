/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:00:25 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 13:07:45 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>

int	ft_printf(const char *fmt, ...);

/* Utility functions */
void	ft_putnbr_unsigned(unsigned int n);
void	ft_putnbr_hex(unsigned int n, int uppercase);
void	ft_putptr(void *ptr);

#endif
