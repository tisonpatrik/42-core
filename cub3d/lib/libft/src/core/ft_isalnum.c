/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:08:37 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/**
 * @brief Tests if a character is alphanumeric
 *
 * This function checks if the given character is alphanumeric.
 * It mimics the behavior of the standard isalnum function.
 * Returns non-zero for characters a-z, A-Z, and 0-9, zero otherwise.
 *
 * @param c The character to test
 * @return Non-zero if character is alphanumeric, zero otherwise
 */
int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (8);
	}
	else if (c >= '0' && c <= '9')
	{
		return (8);
	}
	return (0);
}
