/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:24:11 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mem.h"

/**
 * @brief Copies memory area
 *
 * This function copies n bytes from memory area src to memory area dest.
 * The memory areas must not overlap. Use ft_memmove if the memory areas
 * do overlap. It mimics the behavior of the standard memcpy function.
 *
 * @param dest Pointer to the destination memory area
 * @param src Pointer to the source memory area
 * @param n Number of bytes to copy
 * @return Pointer to dest
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;

	i = 0;
	d = (unsigned char *)dest;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	*src = "Hello from the other side.";
	char		dest[50];
	char		ft_dest[50];

	strcpy(dest,"You are so good....");
	printf("Before: %s \n", dest);
	memcpy(dest, src, strlen(src) + 1);
	printf("After: %s\n", dest);
	strcpy(ft_dest,"You are so good....");
	printf("Before: %s \n", ft_dest);
	ft_memcpy(ft_dest,src, strlen(src) +1);
	printf("After: %s\n", ft_dest);
	assert(strcmp(dest, ft_dest) == 0);
	return (0);
}
*/
