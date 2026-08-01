/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
/**
 * @brief Calculates the length of a string
 *
 * This function counts the number of characters in a null-terminated string.
 * It mimics the behavior of the standard strlen function.
 * The function counts characters until it encounters the null terminator '\0'.
 *
 * @param str The string whose length is to be calculated
 * @return The number of characters in the string (excluding null terminator)
 */

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
