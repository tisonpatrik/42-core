/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:25:02 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 19:06:47 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s);

/**
 * @brief Locates the last occurrence of a character in a string
 *
 * This function returns a pointer to the last occurrence of the character c
 * in the string str. The terminating null byte is considered part of the string,
 * so if c is '\0', the function returns a pointer to the terminator.
 * It mimics the behavior of the standard strrchr function.
 *
 * @param str The string to search
 * @param c The character to locate
 * @return Pointer to the last occurrence of c, or NULL if not found
 */
char	*ft_strrchr(const char *str, int c)
{
	size_t	i;

	i = ft_strlen(str);
	while (1)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		if (i == 0)
			break ;
		i--;
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
	char	*expected;
	char	*current;

	s = "Hello, my friend.";
	c = 't' + 256;
	expected = strrchr(s, c);
	printf("expected: %s \n", expected);
	current = ft_strrchr(s, c);
	printf("current: %s \n", current);
	assert(expected == current);
	return (1);
}
*/
