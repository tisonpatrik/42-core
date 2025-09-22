/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:24:11 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 22:01:45 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mem.h"

/**
 * @brief Sets the first n bytes of memory to zero
 *
 * This function sets the first n bytes of the memory area pointed to by str
 * to zero (bytes containing '\0'). It mimics the behavior of the standard
 * bzero function. This function is commonly used to initialize memory areas.
 *
 * @param str Pointer to the memory area to be zeroed
 * @param n Number of bytes to set to zero
 * @return Pointer to the memory area str
 */
void	*ft_bzero(void *str, size_t n)
{
	unsigned char	*s;
	size_t			i;

	s = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		s[i] = '\0';
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
	char	*str;
	char	expected[50];
	char	current[50];

	i = 1;
	str = "Hello from the other side.";
	
	strcpy(expected, str);
	bzero(expected, i);
	
	strcpy(current, str);
	ft_bzero(current, i);
	

	for (int j = 0; j < (int)strlen(str); j++)
		printf("%c", (unsigned char)expected[j]);
	printf("\n");
	
	for (int j = 0; j < (int)strlen(str); j++)
		printf("%c", (unsigned char)current[j]);
	printf("\n");

	assert(strcmp(current, expected) == 0);
	return (0);
}
*/
