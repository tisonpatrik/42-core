/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/str.h"
#include <stdlib.h>

size_t	ft_strlen(const char *s);

/**
 * @brief Applies a function to each character of a string with index
 *
 * This function creates a new string resulting from successive applications
 * of function 'f' to each character of string 's', passing its index as
 * first argument. Memory for the new string is obtained with malloc and
 * can be freed with free.
 *
 * @param s The string on which to iterate
 * @param f The function to apply to each character and its index
 * @return The string created from successive applications of 'f'
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
#include <ctype.h>
#include <stdio.h>

char	to_upper_wrapper(unsigned int i, char c)
{
	(void)i;
	return (char)toupper((unsigned char)c);
}

int	main(void)
{
	char	*str;
	char	*result;

	str = "Hello";
	result = ft_strmapi(str, to_upper_wrapper);
	if (result)
	{
		printf("Original: %s\n", str);
		printf("Mapped:   %s\n", result);
		free(result);
	}
	return (0);
}
*/
