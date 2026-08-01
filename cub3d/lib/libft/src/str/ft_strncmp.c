/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Compares two strings up to n characters
 *
 * This function compares two strings lexicographically up to n characters.
 * It mimics the behavior of the standard strncmp function.
 * The comparison is done using unsigned characters.
 *
 * @param s1 The first string to compare
 * @param s2 The second string to compare
 * @param n The maximum number of characters to compare
 * @return <0 if s1 is less than s2, 0 if equal, >0 if s1 is greater than s2
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	u1;
	unsigned char	u2;

	while (n > 0)
	{
		u1 = (unsigned char)*s1;
		u2 = (unsigned char)*s2;
		s1++;
		s2++;
		if (u1 != u2)
		{
			return (u1 - u2);
		}
		if (u1 == '\0')
		{
			return (0);
		}
		n--;
	}
	return (0);
}
