/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:24:11 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Compares memory areas
 *
 * This function compares the first n bytes of the memory areas s1 and s2.
 * It mimics the behavior of the standard memcmp function.
 * The comparison is done using unsigned characters.
 *
 * @param s1 Pointer to first memory area
 * @param s2 Pointer to second memory area
 * @param n Number of bytes to compare
 * @return <0 if s1 is less than s2, 0 if equal, >0 if s1 is greater than s2
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;
	int				diff;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		diff = ptr1[i] - ptr2[i];
		if (diff)
			return (diff);
		i++;
	}
	return (0);
}
