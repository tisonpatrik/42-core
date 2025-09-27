/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:37 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/str.h"
/**
 * @brief Locates the first occurrence of a character in a string
 *
 * This function returns a pointer to the first occurrence of the character c
 * in the string s. The terminating null byte is considered part of the string,
 * so if c is '\0', the function returns a pointer to the terminator.
 * It mimics the behavior of the standard strchr function.
 *
 * @param s The string to search
 * @param c The character to locate
 * @return Pointer to the first occurrence of c, or NULL if not found
 */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
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
	char	*expected;
	char	*current;

	s = "Hello, my friend.";
	c = 0;
	expected = strchr(s, c);
	printf("expected: %s \n", expected);
	current = ft_strchr(s, c);
	printf("current: %s \n", current);
	assert(expected == current);
	return (1);
}
*/
