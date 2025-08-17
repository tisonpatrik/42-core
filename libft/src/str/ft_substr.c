/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:24:31 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

/**
 * @brief Creates a substring from a string
 *
 * This function allocates and returns a substring from the string 's'.
 * The substring begins at index 'start' and is of maximum size 'len'.
 * Memory for the new string is obtained with malloc and can be freed with free.
 *
 * @param s The string from which to create the substring
 * @param start The start index of the substring in the string 's'
 * @param len The maximum length of the substring
 * @return The substring, or NULL if the allocation fails
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_of_str;
	char	*dest;

	if (!s)
		return (NULL);
	len_of_str = ft_strlen(s);
	if (start >= len_of_str)
	{
		dest = malloc(1);
		if (!dest)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	if (len > len_of_str - start)
		len = len_of_str - start;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s + start, len + 1);
	return (dest);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*str;
	size_t	len;
	char	*sub;

	str = "Hello my friend, do you have a nice day?";
	unsigned int start= 17;
	len = 25;
	sub = ft_substr(str, start, len);
	printf("sub: %s \n", sub);
}
*/
