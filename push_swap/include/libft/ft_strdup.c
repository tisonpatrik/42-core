/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:57:20 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s);

/**
 * @brief Duplicates a string
 *
 * This function creates a new string which is a duplicate of the string s.
 * Memory for the new string is obtained with malloc, and can be freed with free.
 * It mimics the behavior of the standard strdup function.
 *
 * @param s The string to duplicate
 * @return A pointer to the duplicated string, or NULL if insufficient memory
 */
char	*ft_strdup(const char *s)
{
	size_t	len;
	int		i;
	char	*new_string;

	len = ft_strlen(s);
	new_string = malloc(len + 1 * sizeof(char));
	if (new_string == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

/*
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char	*src;
	char	*expected;
	char	*current;

	src = "654";
	expected = strdup(src);
	current = ft_strdup(src);
	write(1, expected, 1);
	write(1, "\n", 1);
	write(1, current, 1);
	write(1, "\n", 1);
}
*/
