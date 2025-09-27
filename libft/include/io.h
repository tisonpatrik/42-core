/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:28:28 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:33 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

/* Input/Output functions */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_get_line(int fd);
void	ft_putnbr_unsigned(unsigned int n);
void	ft_putnbr_hex(unsigned int n, int uppercase);
void	ft_putptr(void *ptr);

#endif
