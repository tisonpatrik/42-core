/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:28:28 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 12:17:49 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CORE_H
# define FT_CORE_H

# include <stddef.h>

/* Character classification functions */
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);

/* Character transformation functions */
int		ft_tolower(int c);
int		ft_toupper(int c);

/* Conversion functions */
int		ft_atoi(const char *str);

#endif
