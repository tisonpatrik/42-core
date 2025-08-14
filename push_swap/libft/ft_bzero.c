/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:42:23 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 19:08:40 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <strings.h>

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
