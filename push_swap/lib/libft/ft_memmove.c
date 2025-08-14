/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:22:24 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 19:02:31 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * @brief Copies memory area with overlap handling
 *
 * This function copies n bytes from memory area src to memory area dest.
 * The memory areas may overlap: copying takes place as though the bytes
 * in src are first copied into a temporary array that does not overlap
 * with src or dest, and the bytes are then copied from the temporary
 * array to dest. It mimics the behavior of the standard memmove function.
 *
 * @param dest Pointer to the destination memory area
 * @param src Pointer to the source memory area
 * @param n Number of bytes to copy
 * @return Pointer to dest
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;
	size_t				i;

	i = 0;
	d = (unsigned char *)dest;
	if (d == s || n == 0)
		return (dest);
	if (d < s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}

/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	overlap[100] = "1234567890";

	memmove(overlap + 2, overlap, 5);
	printf("overlap: %s\n", overlap);
	char ft_overlap[100]= "1234567890";
	ft_memmove(ft_overlap +2, ft_overlap, 5);
	printf("ft_overlap: %s\n",ft_overlap);
	assert(strcmp(overlap, ft_overlap) == 0);
	return (0);
}
*/
