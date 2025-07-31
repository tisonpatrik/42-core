/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:23:42 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *src);

char	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

size_t	find_start(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	return (i);
}

size_t	find_end(const char *s1, const char *set, size_t start)
{
	size_t	pos;

	pos = ft_strlen(s1) - 1;
	while (pos > 0 && pos != start && is_in_set(s1[pos], set))
		pos--;
	return (pos);
}

/**
 * @brief Trims characters from the beginning and end of a string
 *
 * This function allocates and returns a copy of the string 's1',
 * with the characters specified in 'set' removed from the beginning
 * and the end of the string. Memory for the new string is obtained
 * with malloc and can be freed with free.
 *
 * @param s1 The string to be trimmed
 * @param set The reference set of characters to trim
 * @return The trimmed string, or NULL if the allocation fails
 */
char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	if (set[0] == '\0')
		return (ft_strdup((char *)s1));
	start = find_start(s1, set);
	end = find_end(s1, set, start);
	if (end < start)
		len = 0;
	else
		len = end - start + 1;
	trimmed = (char *)malloc((len + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_memcpy(trimmed, s1 + start, len);
	trimmed[len] = '\0';
	return (trimmed);
}

/*
#include <stdio.h>

int	main(void)
{
	const char	*s1 = "123";
	const char	*set = "";
	char		*result;

	result = ft_strtrim(s1, set);
	if (result)
	{
		printf("Result: \"%s\"\n", result);
		free(result);
	}
	else
	{
		printf("Result is NULL\n");
	}
	return (0);
}
*/
