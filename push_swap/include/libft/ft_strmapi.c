/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:03:24 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
