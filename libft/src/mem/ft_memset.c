/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:24:11 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:33 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mem.h"

/**
 * @brief Fills memory with a constant byte
 *
 * This function fills the first n bytes of the memory area pointed to by str
 * with the constant byte c. 
 * It mimics the behavior of the standard memset function.
 * This function is commonly used to initialize memory areas 
 * with a specific value.
 *
 * @param str Pointer to the memory area to fill
 * @param c The byte value to fill with (converted to unsigned char)
 * @param n Number of bytes to fill
 * @return Pointer to the memory area str
 */
void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*s;
	size_t			i;

	s = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		s[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		i;
	char	c;
	char	*str;
	char	expected[50];
	char	current[50];

	i = 5;
	c = '&';
	str = "Hello from the other side.";
	strcpy(expected, str);
	memset(expected, c, i);
	strcpy(current, str);
	ft_memset(current, c, i);
	printf("e: %s \n", expected);
	printf("c: %s \n", current);
	assert(strcmp(current, expected) == 0);
	return (0);
}
*/
