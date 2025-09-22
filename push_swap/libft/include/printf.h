/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:00:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:28:45 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>

int		ft_printf(const char *fmt, ...);

void	ft_putnbr_unsigned(unsigned int n);
void	ft_putnbr_hex(unsigned int n, int uppercase);
void	ft_putptr(void *ptr);

#endif
