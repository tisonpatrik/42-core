/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:28:28 by ptison            #+#    #+#             */
/*   Updated: 2025/08/18 15:27:02 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <stddef.h>

/* Character classification functions */
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);

/**
 * @brief Check if character is a whitespace character
 *
 * This function checks if the given character is a whitespace character.
 * It mimics the behavior of the standard isspace function.
 * Returns non-zero for space, tab, newline, carriage return, vertical tab, and form feed.
 *
 * @param c The character to test
 * @return Non-zero if character is whitespace, zero otherwise
 */
int		ft_isspace(int c);

/* Character transformation functions */
int		ft_tolower(int c);
int		ft_toupper(int c);

/* Conversion functions */
int		ft_atoi(const char *str);
int		ft_parse_sign(const char **p);

#endif
