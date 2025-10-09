/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:24:11 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:31 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mem.h"

/**
 * @brief Searches for a character in a memory area
 *
 * This function scans the initial n bytes of the memory area pointed to by s
 * for the first instance of c. Both c and the bytes of the memory area are

	* interpreted as unsigned char.
	* It mimics the behavior of the standard memchr function.
 *
 * @param s Pointer to the memory area to search
 * @param c The character to search for (converted to unsigned char)
 * @param n Number of bytes to search
 * @return Pointer to the matching byte, or NULL if not found within n bytes
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr = (const unsigned char *)s;

	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}

/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s;
	int		c;
	size_t	n;
	void	*expected;
	void	*current;

	s = "Hello, my friend.";
	c = 'f';
	n = strlen(s);
	expected = memchr(s, c, n);
	printf("expected: %s\n", (char *)expected);
	current = ft_memchr(s, c, n);
	printf("current: %s\n", (char *)current);
	assert(expected == current);
	return (0);
}
*/
